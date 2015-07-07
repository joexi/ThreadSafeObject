JXMultiThreadObject
===================

A simple adapter to helping using un-thread-safe object in a safe way.

# CODE
using these methods to receive method call and redirect to the target object after thread safe processing.
``` objc
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector {
    return [[_container class] instanceMethodSignatureForSelector:aSelector];
}

- (void)forwardInvocation:(NSInvocation *)anInvocation
{
    NSMethodSignature *sig = [anInvocation valueForKey:@"_signature"];
    const char *returnType = sig.methodReturnType;
    //    NSLog(@"%@ = > %@",anInvocation.target, NSStringFromSelector(anInvocation.selector));
    //    NSLog(@"%s",returnType);
    if (!strcmp(returnType, "v")) {
        /** the setter method just use async dispatch 
         remove the barrier to make it faster when u r sure that invacations will not affect each other
         */
        dispatch_barrier_async(_dispatchQueue, ^{
            [anInvocation invokeWithTarget:_container];
        });
    }
    else {
        /** all getter method need sync dispatch 
         barrier make sure the result is correct
         getter method need barrier in most ways unless u dont except this */
        dispatch_barrier_sync(_dispatchQueue, ^{
            [anInvocation invokeWithTarget:_container];
        });
    }
}
```
# SAMPLE
JXMutableArray, you just need to declare the potocol and no need to implement them
``` objc
@protocol JXMutableArrayProtocol 
@optional
- (id)lastObject;
- (id)objectAtIndex:(NSUInteger)index;

- (NSUInteger)count;

- (void)addObject:(id)anObject;
- (void)insertObject:(id)anObject atIndex:(NSUInteger)index;
- (void)removeLastObject;
- (void)removeObjectAtIndex:(NSUInteger)index;
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(id)anObject;
@end
/** this array is mutable and thread-safe 
 it provides some simple methods to operating an array 
 it is not the fastest way but quite convenient
 */
@interface JXMutableArray : JXMultiThreadObject <JXMutableArrayProtocol>
{
}

```

# HOW TO USE
``` objc
    JXMutableArray *ary = [[JXMutableArray alloc] init];
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    queue.maxConcurrentOperationCount = 10;
    for (int i = 0; i < 200; i++) {
        NSNumber *number = [NSNumber numberWithInt:i];
        [queue addOperationWithBlock:^{
            [ary addObject:number];
        }];
    }
    [queue waitUntilAllOperationsAreFinished];
    NSLog(@"%d",ary.count);
    NSLog(@"%@",ary);
```
