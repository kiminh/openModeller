/**
 * Declaration of MeanVarianceNormalizer class
 * 
 * @author Renato De Giovanni
 * $Id: MeanVarianceNormalizer.hh 3446 2007-07-31 23:41:15Z rdg $
 *
 * LICENSE INFORMATION
 * 
 * Copyright(c) 2007 by CRIA -
 * Centro de Referencia em Informacao Ambiental
 *
 * http://www.cria.org.br
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

#ifndef _MEANVARIANCENORMALIZER_HH
#define _MEANVARIANCENORMALIZER_HH

#include <openmodeller/Normalizer.hh>

class dllexp MeanVarianceNormalizer : public Normalizer {

public:

  // Used only during deserialization
  MeanVarianceNormalizer();

  ~MeanVarianceNormalizer();

  void computeNormalization( const ReferenceCountedPointer<const SamplerImpl>& samplerPtr );

  void normalize( Sample * samplePtr );

  Normalizer * getCopy();
  
  ConfigurationPtr getConfiguration() const;
  
  void setConfiguration( const ConstConfigurationPtr & );

private:
  
  Sample _mean;
  Sample _stddev;

};

#endif
