//========================================================================
// IHandwritingRecSys.h
//========================================================================
// Declarations for the interfeace class for the handwriting recognition
// systems.

#ifndef I_HANDWRITING_REC_SYS_H
#define I_HANDWRITING_REC_SYS_H

// Here we use forward declaration instead of #include. Forward
// declaration is a declaration of an identifier (type, variable, or
// class) before giving a complete definition.
//
// We should use forward declaration whenever possible. Using forward
// declaration is almost always better than using #include because
// #include may have some side effects such as:
// - including other headers you don't need
// - polluting the namespcae
// - longer compilation time

class Image;
class VectorImage;

//------------------------------------------------------------------------
// IHandwritingRecSys
//------------------------------------------------------------------------
// Abstract base class for handwriting recognition systems (HRS)
//
// - train   : Train the HRS with a vector of labeled images
// - classify: Classify an image and return the image that has the minimal
//             Euclidean distance to the given image.
//

class IHandwritingRecSys {
 public:
  virtual void  train( const VectorImage& v )  = 0;
  virtual Image classify( const Image& image ) = 0;
};

#endif  // IHRS_H
