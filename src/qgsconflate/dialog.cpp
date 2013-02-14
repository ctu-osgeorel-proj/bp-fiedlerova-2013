// Local includes
#include "dialog.h"

// QT includes
#include <QMessageBox>

// QGis includes
#include <qgsmapcanvas.h>
#include <qgsvectorlayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsogrprovider.h>
#include <qgsvectorfilewriter.h>
#include <qgsvectorlayerimport.h>
#include <qgsvectorlayerfeatureiterator.h>


// GEOS includes
#include <geos_c.h>
#include <geos/export.h>

#include <iostream>


Dialog::Dialog(QWidget *parent, Qt::WFlags fl, QgisInterface * iface) :
    QDialog(parent, fl)
{
    setupUi(this);

    // set interface
    mIface = iface;

    // initialize data
    mRefLayer = NULL;
    mSubLayer = NULL;

    // load map layers to the QMap container
    QMap<QString, QgsMapLayer*> mapLayers = QgsMapLayerRegistry::instance()->mapLayers();
    QMap<QString, QgsMapLayer*>::iterator layer_it = mapLayers.begin();

    //
    for ( ; layer_it != mapLayers.end(); ++layer_it )
    {
        // map layer as vector layer
        QgsVectorLayer* vl = dynamic_cast<QgsVectorLayer*>( layer_it.value() );

        // stop if it is not vector layer
        if ( !vl )
          continue;

        // add layer name to comboBox
        this->mcbReferences->insertItem( 0, vl->name() );
        this->mcbSubjects->insertItem( 0, vl->name() );
    }

} // constructor


Dialog::~Dialog()
{

}  // destructor


QgsVectorLayer* Dialog::selectedLayer(int index)
{

  // load map layers to the QMap container
  QMap<QString, QgsMapLayer*> mapLayers = QgsMapLayerRegistry::instance()->mapLayers();
  QMap<QString, QgsMapLayer*>::iterator layer_it = mapLayers.begin();

  // find the right layer
  for ( ; layer_it != mapLayers.end(); ++layer_it )
  {

    QgsVectorLayer* vl = dynamic_cast<QgsVectorLayer*>( layer_it.value() );

    if ( !vl )
      continue;

    // return layer according to selected name
    if ( (index == 0) && (vl->name() == mcbReferences->currentText()) )
      return vl;

    if( (index == 1) && (vl->name() == mcbSubjects->currentText()) )
        return vl;

  }

  // return NULL if there is no vector layer
  return NULL;

} // QgsVectorLayer* Dialog::selectedLayer(int index)


bool Dialog::copyLayer()
{
    // reference layer
    mSubLayer = selectedLayer(1);

    // stop if there is no reference layer
    if( mSubLayer == NULL )
    {
        qDebug("No layer");
        QMessageBox::information(0,"Information","No Layer!", QMessageBox::Ok);
        return false;
    }

    // new vector layer as copy of mRefLayer
    QMap<int, int> *oldToNewAttrIdxMap = new QMap<int, int>;

    // parameters of new vector layer
    QString uri = mSubLayer->source()+"_copy.shp";
    QString *errorMessage = NULL;
    bool overwrite = false;
    QMap <QString, QVariant> *options = new QMap<QString, QVariant>;
    options->insert("fileEncoding", "utf-8");
    options->insert("driverName", "ESRI Shapefile");
    QgsFields fields = mSubLayer->pendingFields(); //mSubLayer->dataProvider()->fields();
    QGis::WkbType wkbType = mSubLayer->wkbType();
    QgsCoordinateReferenceSystem srs = (mSubLayer->crs());

    if( fields.isEmpty() )
        qDebug("Fields are empty");

    // create empty layer
    //QgsVectorLayerImport::ImportError ierror =
    QgsOgrProvider::createEmptyLayer(uri, fields, wkbType, &srs, overwrite, oldToNewAttrIdxMap, errorMessage,
                                     options);
    /*if( !ierror )
    {
        QMessageBox::warning(0,"Error", "Error while creating layer", QMessageBox::Ok);
        return false;
    }*/

    qDebug( "Empty vector layer created." );

    //new layer
    QgsVectorLayer *myLayer = new QgsVectorLayer(uri, mSubLayer->name()+"_copy", mSubLayer->providerType(), "ogr");
    qDebug( "New vector layer created." );


    // copy features from subject layer to the new layer
    QgsFeature myFeature;
    QgsFeatureRequest request = QgsFeatureRequest(); // default feature request
    QgsVectorLayerFeatureIterator featureIt = QgsVectorLayerFeatureIterator(mSubLayer, request); // feature iterator
    featureIt.rewind(); // reset iterator to the start position
    QList<QgsFeature> features;
    while( featureIt.nextFeature( myFeature ) )
    {
        // add feature
        features.push_back( myFeature );

    }

    if(myLayer->dataProvider()->addFeatures(features))
        qDebug( "Features added." );
    else
        qDebug( "Unable to add features." );

   // myLayer->commitChanges();

    // add layer if valid
    if(myLayer->isValid())
    {
        qDebug("Layer is valid");
        // add new layer to the layer registry
        QgsMapLayerRegistry::instance()->addMapLayers( QList<QgsMapLayer *>() << myLayer);
        return true;
    }
    // invalid layer
    else
    {
        qDebug("Layer is NOT valid");
    }

    return false;

} // bool Dialog::copyLayer()


void Dialog::transferGeometrytoGeos( QgsVectorLayer *theLayer, unsigned short layer )
{
    // empty geometry
    QgsGeometry *geom = NULL;

    if ( layer == 0 )
    {
        mGeosRef.clear();
    }
    else
    {
        mGeosSub.clear();
    }


    // transfer geometry of each feature from subject layer to geos
    QgsFeature myFeature;

    while( theLayer->nextFeature(myFeature) )
    {
        // geometry of the feature
        geom = myFeature.geometry();

        // transfer qgis geometry to geos
        MyGEOSGeom geos;
        //geos.setGEOSgeom( geom->asGeos() );

        // add geometry to the list of geos geometries
        if (layer == 0) // reference layer
        {
            mGeosRef.push_back(geos);
        }
        else
        {
            mGeosSub.push_back(geos);
        }

    }


} // bool Dialog::transferGeometryToGeos()


void Dialog::transferGeometryFromGeos( )
{

    // AFTER DOING SOMETHING WITH GEOMETRY IN GEOS FORMAT

    QgsGeometry *geom = NULL;

    // change geometry in the layer according to GEOS geometry
    QgsFeature myFeature;

    for( TGeomLayer::iterator it = mGeosSub.begin(); mGeosSub.end() != it; it++ )
    {
        // next feature in the layer
        if ( mSubLayer->nextFeature(myFeature) )
        {
            // set new geometry to the feature from geos geometry
            //geom->fromGeos( (*it).getGEOSGeom() );
            mSubLayer->changeGeometry( myFeature.id(), geom );
        }

    }

} // bool Dialog::transferGeometryFromGeos()


void Dialog::vertexSnap()
{

    //initGEOS(); ???
    transferGeometrytoGeos( mSubLayer, 1 );
    transferGeometrytoGeos( mRefLayer, 0 );

    // DO SOMETHING WITH GEOMETRY IN GEOS FORMAT
    VertexSnapper vs;

    // set geometries of layers to vertex snapper
    vs.setRefGeometry( mGeosRef );
    vs.setSubGeometry( mGeosSub );

    // set tolerance distance
    vs.setTolDistance( 1 );

    // snap vertices from subject layer to the reference layer
    vs.snap();

    //finishGEOS(); ???

} // void Dialog::vertexSnap()


void Dialog::on_okButton_clicked()
{

    if( copyLayer() )
    {
        //vertexSnap();
        qDebug("Layer was copied.");
    }
    else
    {
        qDebug("No layer was copied.");
        QMessageBox::information(0,"Information","No Layer was copied!", QMessageBox::Ok);
    }

} // void Dialog::on_okButton_clicked()


void Dialog::on_closeButton_clicked()
{
    this->close();
} // void Dialog::on_closeButton_clicked()
