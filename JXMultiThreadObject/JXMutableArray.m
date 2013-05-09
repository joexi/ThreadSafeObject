//
//  JXMutableArray.m
//  Test
//
//  Created by Joe on 13-5-8.
//  Copyright (c) 2013年 Joe. All rights reserved.
//

#import "JXMutableArray.h"

@implementation JXMutableArray
- (id)init
{
    self = [super init];
    if (self) {
        self.container = [NSMutableArray array];
    }
    return self;
}

@end
