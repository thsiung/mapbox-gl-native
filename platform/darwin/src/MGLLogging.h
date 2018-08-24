#import <Foundation/Foundation.h>

#import "MGLFoundation.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MGLLoggingLevel) {
    
    MGLLoggingLevelNone = 0,
    
    MGLLoggingLevelInfo,
    
    MGLLoggingLevelDebug,
    
    MGLLoggingLevelError,
    
    MGLLoggingLevelFault,
    
};

typedef void (^MGLLoggingBlockHandler)(MGLLoggingLevel, NSString *, NSString *);

MGL_EXPORT
@interface MGLLogging : NSObject

@property (nonatomic, copy, null_resettable) MGLLoggingBlockHandler handler;
@property (assign, nonatomic) MGLLoggingLevel loggingLevel;

+ (instancetype)sharedInstance;

@end

NS_ASSUME_NONNULL_END
