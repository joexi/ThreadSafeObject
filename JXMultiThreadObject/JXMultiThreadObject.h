//
//  JXMultiThreadObject.h
//  Test
//
//  Created by Joe on 13-5-9.
//  Copyright (c) 2013年 Joe. All rights reserved.
//

#import <Foundation/Foundation.h>
/** this class makes Non-thread-safe object works like thread-safe object
 a little loss of performance may cause when u using this class to operating an object
 u can inherit this class and override the rule of dispathing to improve the performance
 in some situation it will work batter than the origin class
 */
@interface JXMultiThreadObject : NSObject
{
    dispatch_queue_t _dispatchQueue;
    NSObject *_container;
}
@property (nonatomic, strong) NSObject *container;
@end
