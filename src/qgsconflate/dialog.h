/***************************************************************************
    dialog.h

    Dialog
    dialog for plugin Conflate

    ---------------------
    begin                : April 2013
    copyright            : (C) 2013 by Tereza Fiedlerová
    email                : tfiedlerova dot at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DIALOG_H
#define DIALOG_H

// Local includes
#include "ui_dialog.h"
#include "qgsconflateprovider.h"
#include "geoc.h"

// Qt includes
#include <QDialog>
#include <QtGui>

// QGIS includes
#include <qgisinterface.h>


/** Class which provides GUI for plugin. */

class Dialog : public QDialog, private Ui::Dialog
{
    Q_OBJECT

public:

    Dialog(QWidget *parent = 0, Qt::WFlags fl = 0, QgisInterface *iface = 0);
    ~Dialog();

    /** Returns selected layer.
     *  @param index Index of the layer - 0 for reference, 1 for subject
     *  @return selected layer as QgsVectorLayer *
     */
    QgsVectorLayer* selectedLayer( int index );

    /** Load opened layers to combo boxes.
      */
    void loadLayers();

    /** Set conflation parameters from dialog and copy layer.
      * @return True if layer was copied succesfully.
      */
    bool setConflation();

    /** Do the conflation.
      */
    void conflate();

    /** Add new layer to the layer registry.
      */
    void addLayer();

private slots:

    /** Copy reference layer. */
    void on_processButton_clicked();

    /** Close dialog. */
    void on_closeButton_clicked();

    /** Select where to save layer. */
    void on_selectButton_clicked();

    /** Refresh values in comboBoxes and more. */
    void on_refreshButton_clicked();

    /** Enable or disable other elements for line match. */
    void on_mrbLineMatch_toggled(bool checked);

    /** Show or hide help. */
    void on_helpButton_clicked();

private:

    QgisInterface *mIface;
    QgsConflateProvider* mConflate;
    QString mProtocol;
    bool help;

};

#endif // DIALOG_H
