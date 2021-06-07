#ifndef __RSID_FACEPRINTS_COMMON_DEFINES_H__
#define __RSID_FACEPRINTS_COMMON_DEFINES_H__

// This file contains common matcher and vector related defines, that are used on host and device sides. 
// This file should be compiled in C and C++ compilers - so we can use it in both C and C++ clients.
// For this reason - only structs used here (no classes).
//
#ifdef __cplusplus
namespace RealSenseID
{
#endif // __cplusplus

#define RSID_FACEPRINTS_VERSION							        (8)

#define RSID_NUM_OF_RECOGNITION_FEATURES	                    (256)
// 3 extra elements (1 for hasMask , 1 for norm, 1 spare).
#define RSID_FEATURES_VECTOR_ALLOC_SIZE                         (259) // for DB element vector alloc size.
#define RSID_INDEX_IN_FEATURES_VECTOR_TO_FLAGS                  (256)

#define RSID_EXTRACTED_FEATURES_VECTOR_ALLOC_SIZE               (259) // for Extracted element vector alloc size.

typedef short feature_t;

typedef enum FaceprintsType
{
    W10 = 0,
    RGB,
    NUMBER_OF_FACEPRINTS_TYPES
} FaceprintsTypeEnum;

typedef enum FaOperationFlags
{
    OpFlagError1 = 0,
    OpFlagAuthWithoutMask = 1,
    OpFlagAuthWithMask = 2,
    OpFlagEnrollWithoutMask = 3,
    OpFlagError2 = 4,
    NumOpFlags
} FaOperationFlagsEnum;

typedef enum FaVectorFlags
{
    VecFlagNotSet = 0,
    VecFlagValidWithMask = 1,
    VecFlagValidWithoutMask = 2,
    VecFlagInvalid = 3,
    VecFlagError1 = 4,
    VecFlagError2 = 5,
    NumVecFlags
} FaVectorFlagsEnum;

// extracted faceprints element
// a reduced structure that is used to represent the extracted faceprints been transferred from the device to the host
// through the packet layer. 
typedef struct ExtractedFaceprintsElement
{
    int version;
    
    int featuresType;
    
    int flags;
    
    feature_t featuresVector[RSID_EXTRACTED_FEATURES_VECTOR_ALLOC_SIZE];

#ifdef __cplusplus
    ExtractedFaceprintsElement()
    {
        version = (int)RSID_FACEPRINTS_VERSION;
        flags = 0;
    }
#endif
} ExtractedFaceprints_t;

// db layer faceprints element.
// a structure that is used in the DB layer, to save user faceprints and metadata to the DB.
// the struct includes several vectors and metadata to support all our internal matching mechanism (e.g. adaptive-learning).
typedef struct DBFaceprintsElement
{
    int reserved[5]; // reserved placeholders (to minimize chance to re-create DB).

    int version;
    
    int featuresType;

    int flags; // flags - generic flags to indicate whatever we need.

    // enrollmentDescriptor - is the enrollment faceprints per user.
    // adaptiveDescriptorWithoutMask - is the ongoing faceprints per user with mask (we update it over time).
    // adaptiveDescriptorWithMask - is the ongoing faceprints per user with mask (we update it over time).
    feature_t adaptiveDescriptorWithoutMask[RSID_FEATURES_VECTOR_ALLOC_SIZE];
    feature_t adaptiveDescriptorWithMask[RSID_FEATURES_VECTOR_ALLOC_SIZE];
    feature_t enrollmentDescriptor[RSID_FEATURES_VECTOR_ALLOC_SIZE];

#ifdef __cplusplus
    DBFaceprintsElement()
    {
        version = (int)RSID_FACEPRINTS_VERSION;
        featuresType = (int)(FaceprintsTypeEnum::W10);
        flags = 0;
    }
#endif
} Faceprints_t; 

// [MatchElement_t] is a reduced structure that we use to match a single faceprints vector
// against DB faceprint objects during authentication (using Matcher Api functions).
typedef ExtractedFaceprints_t MatchElement_t;

// [ExtractedSecureVersionDescriptor] - is used to transfer faceprints from device to host.
// [DBSecureVersionDescriptor] - is used to save user faceprints and metadata object to DB.
typedef Faceprints_t DBSecureVersionDescriptor; 
typedef ExtractedFaceprints_t ExtractedSecureVersionDescriptor;   

// these definitions to be used in C clients (e.g. rsid_c_client.cc):
// rsid_extracted_faceprints_t - a packet layer element faceprints (as extracted from the device).
// rsid_faceprints_t - a db layer element faceprints (includes additional vectors and metadata).
typedef ExtractedFaceprints_t   rsid_extracted_faceprints_t;
typedef Faceprints_t            rsid_faceprints_t;

#ifdef __cplusplus
} // close namespace RealSenseID
#endif // __cplusplus

#endif // __RSID_FACEPRINTS_COMMON_DEFINES_H__



