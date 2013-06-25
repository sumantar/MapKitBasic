//
//  PVCharacter.h
//  Park View
//
//  Created by sumantar on 25/06/13.
//  Copyright (c) 2013 Chris Wagner. All rights reserved.
//

#import <MapKit/MapKit.h>

@interface PVCharacter : MKCircle

@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) UIColor *color;

@end
