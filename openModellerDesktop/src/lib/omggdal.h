/***************************************************************************
 *   Copyright (C) 2005 by Tim Sutton   *
 *   tim@linfiniti.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef OMGGDAL_H
#define OMGGDAL_H

#include <QObject>
#include "gdal_priv.h"
class QString;

/** \ingroup library
 * \brief A structure for holding raster band stats.
 */
struct BandStats {
	QString bandName;
	int bandNo;
	double minValDouble;
	double maxValDouble;
	//the distance between min & max
	double rangeDouble;
	double meanDouble;
	double sumSqrDevDouble; //used to calculate stddev
	double stdDevDouble;
	double sumDouble;
	int elementCountInt;
	double noDataDouble;
};

  int CPL_STDCALL progressCallback( double dfComplete, const char *pszMessage,
                       void * pProgressArg );

/** \ingroup library
 * \brief This class will write a png image given an input gdal compatible datasource, and 
 * provide other GDAL related functions in Qt friendly way.
 **/
class OMG_LIB_EXPORT OmgGdal : public QObject
{
  Q_OBJECT;

public:
  //declare eums first!
  enum FileType {GeoTiff,ArcInfoAscii};

  OmgGdal();
  ~OmgGdal();

  const QString getWorldFile(const QString theFileName) ;
  const QString getAsciiHeader(const QString theFileName) ;
  /**
  * A Qt style wrapper for gdal to convert from one file format to another.
  * @see FileType enum for the currently supported output file types
  * @param const QString theInputFile the name of the input file
  * @param const QString theOutputFileName the name of the output file
  * @param const FileType theFileType the type of the output file
  * @return const bool true on success
  */
  const bool convert(const QString theInputFile, const QString theOutputFileName, const FileType theOutputFileType) ;

  /**
  * A Qt style wrapper for gdal to resize a file.
  * @see FileType enum for the currently supported input file types
  * @param const QString theInputFile the name of the input file
  * @param const QString theOutputFileName the name of the output file
  * @param const int theWidth the width of output image
  * @param const int theHeight the height of output image
  * @return const bool true on success
  */
  //  const bool gdalResize(const QString theFileName, const QString theOutputFileName, const int theWidth, const int theHeight){};

  /** Get a list of supported GDAL datatype file filters.
  *   @NOTE THis method was copied over from QGIS QgsRasterLayer
  *   @param A reference to a string. This will be populated with the results.
  *   @return void
  */
  void buildSupportedRasterFileFilter(QString & theFileFiltersString);

  /** Create contour lines from probability surface
  * Only the first raster band will be contoured.Contours are fixed at 10 unit increments.
  * @NOTE This method is based on the GDAL apps/gdal_contour.cpp sources
  * @param const QString theInputFile Gdal dataset to be contoured
  * @param const QString the name of the generated shapefile
  */
  const QString contour(const QString theInputFile);
  /** Call the emitter a progress signal.
  * @NOTE We need this level of indirection to support gdal style call backs.
  * @see updateProgress
  */
  void showProgress (int theProgress,int theMaximum);
  /**
  * A simple test to see if a file is a valid gdal raster.
  * @param QString the name of the file to test
  * @return bool True if file is valid
  */
  static bool isValidGdalFile(const QString theFilename);
  /**
  * A simple test to see if a gdal raster has a valid projection
  * @param QString the name of the file to test
  * @return bool True if file is valid
  */
  static bool isValidGdalProj(const QString theFilename);

  /** Write a pseudocolour PNG out with user specified size.
   * @param theInputFileString A valid gdal raster layer
   * @param theOutFileString The name of the desired output image which
   *        will contain a pseudocolor image of the input layer.
   * @param theHeight - height in pixels for the output image
   * @param theWidth - width in pixels for the output image
   */
  void writeImage(QString theInputFileString, 
    QString theOutputFileString,
    int theWidth,
    int theHeight);
  /** This method will return a pixmap legend representation for the 
   *  pseudocolor ramp used. 
   *  @return true on success, false on failure*/
  const bool makeLegend(const QString theOutputFileName, const int theWidth);
  /** Convert a gdal raster to another gdal raster format.
   * @param theFileName - raster to be converted
   * @param theOutputFileName - name of new raster to be created
   * @param theFormat - GDAL format as per http://www.gdal.org/formats_list.html
   */
  const bool gdal2gdal(const QString theFileName, 
    const QString theOutputFileName,
    const QString theFormat);
  const bool gdal2Tiff(const QString theFileName, const QString theOutputFileName);
  const bool gdal2Ascii(const QString theFileName, const QString theOutputFileName);
signals:
  void error (QString theError);
  /** Emit a progress signal.
  * @NOTE should only ever be called using the showProgress method so we can properly 
  * support gdal style callbacks
  * @see showProgress
  */
  void updateProgress (int theProgress,int theMaximum);

private:

  /** Calculate image statistics */
  void calculateStats(BandStats * theBandStats,GDALDataset * gdalDataset);

};
#endif //OMGGDAL_H
