#include <cstdlib>
#include <iostream>
#include <ctime>

#include <QString>

#include <qgsmaplayer.h>
#include <qgsvectorlayer.h>
#include <qgsproviderregistry.h>

#include "qgsconflateprovider.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

static int parse_opt(int, const char **, QString &, QString &, QString &, short &, double &);
static QgsVectorLayer *open_layer(QString, QString);

void log_and_exit(const char *fmt, ...) {
    va_list ap;
    fprintf( stdout, "ERROR: ");

    va_start (ap, fmt);
    vfprintf( stdout, fmt, ap);
    va_end(ap);
    fprintf( stdout, "\n" );
    exit(1);
}

void notice(const char *fmt, ...) {
    va_list ap;

    fprintf( stdout, "NOTICE: ");

    va_start (ap, fmt);
    vfprintf( stdout, fmt, ap);
    va_end(ap);
    fprintf( stdout, "\n" );
}

int main(int argc, const char **argv)
{
    //initGEOS(notice, log_and_exit); -> only with C api

    QString input_ref, input_sub, output;
    short method;
    double tolerance;

    QgsVectorLayer *refLayer;
    QgsVectorLayer *subLayer;
    QgsVectorLayer *newLayer;

    QgsConflateProvider *cProvider;

    if (0 != parse_opt(argc, argv, input_ref, input_sub, output, method, tolerance))
        return EXIT_FAILURE;

    QgsProviderRegistry::instance("/opt/Quantum-GIS/build/output/lib/qgis/plugins/");

    cProvider = new QgsConflateProvider();

    // load ref layer
    refLayer = open_layer(input_ref, "input_ref");
    if (!refLayer)
        exit(EXIT_FAILURE);

    // load second input layer
    subLayer = open_layer(input_sub, "input_sub");
    if (!subLayer)
        exit(EXIT_FAILURE);


    clock_t start = clock(); // start of measuring time

    cProvider->setRefVectorLayer(refLayer);
    cProvider->setSubVectorLayer(subLayer);
    cProvider->setTolDistance(tolerance);
    cProvider->setMatchCriterium(0.7);
    cProvider->setRepair(false);

    // create output layer
    cProvider->copyLayer(output + ".shp");

    // do something ...
    if(method == 1)
    {
       cProvider->vertexSnap();
    }
    else if(method == 2)
    {
        cProvider->align();
    }
    else if(method == 3)
    {
        cProvider->lineMatch();
    }

    newLayer = cProvider->getNewVectorLayer();

    clock_t end = clock();    // end of measuring time

    std::cout<< ((double)(end - start)/CLOCKS_PER_SEC) << std::endl;

    //finishGEOS();

    exit(EXIT_SUCCESS);
}

int parse_opt(int argc, const char **argv, QString &input_ref, QString &input_sub, QString &output, short &method, double &tolerance)
{
    if (argc != 6) {
        cerr << "Usage: input_ref input_sub output method tolerance" << endl;
        return -1;
    }

    input_ref = argv[1];
    input_sub = argv[2];
    output    = argv[3];
    method    = QString(argv[4]).toShort();
    tolerance = QString(argv[5]).toDouble();

    return 0;
}

QgsVectorLayer *open_layer(QString uri, QString basename)
{
    QgsVectorLayer *pLayer;

    pLayer = new QgsVectorLayer(uri, basename, "ogr");
    if (!pLayer || !pLayer->isValid()) {
        cerr << "Unable to open " << uri.toStdString() << endl;
        return NULL;
    }

    return pLayer;
}
