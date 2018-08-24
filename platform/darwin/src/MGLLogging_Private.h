#import "MGLLogging.h"

@interface MGLLogging (Private)

- (void)logPath:(NSString *)filePath withInfoMessage:(id)message, ...;
- (void)logPath:(NSString *)filePath withDebugMessage:(id)message, ...;
- (void)logPath:(NSString *)filePath withErrorMessage:(id)message, ...;
- (void)logPath:(NSString *)filePath withFaultMessage:(id)message, ...;

@end
