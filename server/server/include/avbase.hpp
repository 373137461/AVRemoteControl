#pragma once

#define  AV_USE_NAMESPACE

#ifdef AV_USE_NAMESPACE
#define  AV_NAMESPACE_BEGIN namespace av{
#define AV_NAMESPACE_END }
#else
#define AV_NAMESPACE_BEGIN
#define  AV_NAMESPACE_END
#endif // AV_USE_NAMESPACE