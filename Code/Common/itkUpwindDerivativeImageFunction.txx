/*==========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkUpwindDerivativeImageFunction.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.
  
==========================================================================*/
#ifndef _itkUpwindDerivativeImageFunction_txx
#define _itkUpwindDerivativeImageFunction_txx

namespace itk
{

/**
 *
 */
template <class TInputImage>
void
UpwindDerivativeImageFunction<TInputImage>
::SetInputImage( InputImageType * ptr )
{
  this->Superclass::SetInputImage( ptr );

  m_ImageSize = 
    this->GetInputImage()->GetLargestPossibleRegion().GetSize();
  
  m_Speed = 1.0;

}


/**
 *
 */
template<class TInputImage>
void
UpwindDerivativeImageFunction<TInputImage>
::PrintSelf(std::ostream& os, Indent indent)
{
  this->Superclass::PrintSelf(os,indent);
  os << indent << "calculate upwind derivative:" << std::endl;
  os << indent << "speed: " << m_Speed << std::endl;
}


/**
 *
 */
template <class TInputImage>
double
UpwindDerivativeImageFunction<TInputImage>
::Evaluate(
const IndexType& index,
unsigned int dim ) const
{
  
  if( !m_Image || dim > ImageDimension - 1 )
    {
    return 0.0;
    }

  m_Derivative = 0.0;
  m_NeighIndex = index ;

  m_CenterValue = (double) m_Image->GetPixel( index );
  
  // calculate backward difference
  if( m_Speed > 0 && index[dim] > 0 )
    {
    m_NeighIndex[dim] = index[dim] - 1;
    m_Derivative = m_CenterValue - (double) m_Image->GetPixel( m_NeighIndex );
    }

  // calculate forward difference
  if( m_Speed <= 0 && index[dim] < m_ImageSize[dim] - 1 )
    {
    m_NeighIndex[dim] = index[dim] + 1;
    m_Derivative = (double) m_Image->GetPixel( m_NeighIndex ) - m_CenterValue;
    }

  return ( m_Derivative );

}


} // namespace itk

#endif
