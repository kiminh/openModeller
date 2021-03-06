/**
 * Definition of AreaStats class 
 * 
 * @file area_stats.hh
 * @author Ricardo Scachetti Pereira (rpereira@ku.edu)
 * @date 2004-10-18
 * $Id: AreaStats.cpp 2419 2006-11-30 13:59:38Z rdg $
 *
 * LICENSE INFORMATION
 * 
 * Copyright(c), The Center for Research, University of Kansas, 
 *                 2385 Irving Hill Road, Lawrence, KS 66044-4755, USA.
 *
 * http://www.nhm.ku.edu
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details:
 * 
 * http://www.gnu.org/copyleft/gpl.html
 */


#include <openmodeller/AreaStats.hh>
#include <openmodeller/Configuration.hh>

AreaStats::AreaStats(Scalar predictionThreshold)
{
  reset(predictionThreshold);
}

AreaStats::AreaStats(const AreaStats *areaStats) :
  _areaTotal( areaStats->getTotalArea() ),
  _areaPredPresent( areaStats->getAreaPredictedPresent() ),
  _areaPredAbsent( areaStats->getAreaPredictedAbsent() ),
  _areaNotPredicted( areaStats->getAreaNotPredicted() ),
  _predictionThreshold( areaStats->getPredictionThreshold() )
{ }

AreaStats::~AreaStats()
{
}

void AreaStats::reset(Scalar predictionThreshold)
{
  _predictionThreshold = predictionThreshold;
  _areaTotal = _areaPredPresent = _areaPredAbsent = _areaNotPredicted = 0;
}


void AreaStats::addPrediction(Scalar value)
{
  _areaTotal++;
  if (value >= _predictionThreshold)
    { _areaPredPresent++; }
  else 
    { _areaPredAbsent++; }
}


void AreaStats::addNonPrediction()
{
  _areaTotal++;
  _areaNotPredicted++;
}


ConfigurationPtr 
AreaStats::getConfiguration() const
{
  ConfigurationPtr config( new ConfigurationImpl("AreaStatistics") );

  config->addNameValue( "TotalCells", _areaTotal );
  config->addNameValue( "CellsPredicted", _areaPredPresent );
  config->addNameValue( "PredictionThreshold", _predictionThreshold );

  return config;
}

