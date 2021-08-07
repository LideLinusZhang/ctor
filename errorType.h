#ifndef CTOR_ERRORTYPE_H
#define CTOR_ERRORTYPE_H

enum ErrorType
{
    InvalidBuildOrImprove,
    InvalidRoll,
    InvalidCommand,
    InsufficientResource,
    InsufficientResourceOther,
    InvalidInput, // Fallback error option
};

#endif //CTOR_ERRORTYPE_H
