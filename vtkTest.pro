QT       += core
CONFIG += c++11

QMAKE_CXXFLAGS+=/utf-8

HEADERS += \
    vtkGloble.h \
    vtkModelInit.h

SOURCES += \
    main.cpp \
    vtkGloble.cpp

include(mySWInteractorStyle/mySWInteractorStyle.pri)


win32:CONFIG(release, debug|release): LIBS += \
-L'C:/Program Files/VTK/lib/' -lvtkChartsCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkCommonColor-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkCommonComputationalGeometry-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkCommonCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkCommonDataModel-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkCommonExecutionModel-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkCommonMath-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkCommonMisc-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkCommonSystem-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkCommonTransforms-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkDICOMParser-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkDomainsChemistry-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkDomainsChemistryOpenGL2-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkdoubleconversion-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkexodusII-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkexpat-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersAMR-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersExtraction-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersFlowPaths-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersGeneral-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersGeneric-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersGeometry-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersHybrid-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersHyperTree-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersImaging-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersModeling-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersParallel-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersParallelImaging-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersPoints-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersProgrammable-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersSelection-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersSMP-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersSources-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersStatistics-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersTexture-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersTopology-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersVerdict-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkfreetype-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkGeovisCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkgl2ps-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkglew-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkGUISupportQt-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkGUISupportQtSQL-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkhdf5-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkhdf5_hl-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingColor-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingFourier-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingGeneral-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingHybrid-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingMath-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingMorphological-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingSources-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingStatistics-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkImagingStencil-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkInfovisCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkInfovisLayout-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkInteractionImage-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkInteractionStyle-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkInteractionWidgets-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOAMR-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOAsynchronous-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOCityGML-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOEnSight-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOExodus-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOExport-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOExportOpenGL2-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOExportPDF-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOGeometry-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOImage-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOImport-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOInfovis-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOLegacy-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOLSDyna-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOMINC-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOMovie-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIONetCDF-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOParallel-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOParallelXML-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOPLY-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOSegY-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOSQL-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOTecplotTable-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOVeraOut-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOVideo-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOXML-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkIOXMLParser-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkjpeg-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkjsoncpp-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtklibharu-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtklibxml2-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtklz4-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtklzma-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkmetaio-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkNetCDF-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkogg-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkParallelCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkpng-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkproj-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkpugixml-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingAnnotation-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingContext2D-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingContextOpenGL2-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingFreeType-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingGL2PSOpenGL2-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingImage-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingLabel-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingLOD-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingOpenGL2-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingQt-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingVolume-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingVolumeOpenGL2-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtksqlite-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtksys-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtktheora-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtktiff-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkverdict-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkViewsContext2D-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkViewsCore-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkViewsInfovis-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkViewsQt-8.2 \
-L'C:/Program Files/VTK/lib/' -lvtkzlib-8.2

else:win32:CONFIG(debug, debug|release): LIBS += \
-L'C:/Program Files/VTK/lib/' -lvtkChartsCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkCommonColor-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkCommonComputationalGeometry-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkCommonCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkCommonDataModel-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkCommonExecutionModel-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkCommonMath-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkCommonMisc-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkCommonSystem-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkCommonTransforms-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkDICOMParser-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkDomainsChemistry-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkDomainsChemistryOpenGL2-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkdoubleconversion-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkexodusII-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkexpat-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersAMR-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersExtraction-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersFlowPaths-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersGeneral-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersGeneric-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersGeometry-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersHybrid-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersHyperTree-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersImaging-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersModeling-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersParallel-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersParallelImaging-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersPoints-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersProgrammable-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersSelection-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersSMP-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersSources-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersStatistics-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersTexture-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersTopology-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkFiltersVerdict-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkfreetype-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkGeovisCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkgl2ps-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkglew-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkGUISupportQt-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkGUISupportQtSQL-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkhdf5-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkhdf5_hl-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingColor-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingFourier-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingGeneral-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingHybrid-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingMath-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingMorphological-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingSources-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingStatistics-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkImagingStencil-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkInfovisCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkInfovisLayout-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkInteractionImage-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkInteractionStyle-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkInteractionWidgets-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOAMR-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOAsynchronous-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOCityGML-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOEnSight-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOExodus-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOExport-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOExportOpenGL2-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOExportPDF-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOGeometry-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOImage-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOImport-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOInfovis-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOLegacy-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOLSDyna-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOMINC-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOMovie-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIONetCDF-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOParallel-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOParallelXML-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOPLY-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOSegY-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOSQL-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOTecplotTable-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOVeraOut-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOVideo-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOXML-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkIOXMLParser-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkjpeg-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkjsoncpp-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtklibharu-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtklibxml2-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtklz4-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtklzma-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkmetaio-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkNetCDF-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkogg-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkParallelCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkpng-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkproj-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkpugixml-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingAnnotation-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingContext2D-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingContextOpenGL2-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingFreeType-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingGL2PSOpenGL2-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingImage-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingLabel-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingLOD-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingOpenGL2-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingQt-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingVolume-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkRenderingVolumeOpenGL2-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtksqlite-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtksys-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtktheora-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtktiff-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkverdict-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkViewsContext2D-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkViewsCore-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkViewsInfovis-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkViewsQt-8.2d \
-L'C:/Program Files/VTK/lib/' -lvtkzlib-8.2d


INCLUDEPATH += 'C:/Program Files/VTK/include/vtk-8.2'
DEPENDPATH += 'C:/Program Files/VTK/include/vtk-8.2'
