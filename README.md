JXMultiThreadObject
===================

a simple class helping using un-thread-safe class in a safe way

# SAMPLE
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
