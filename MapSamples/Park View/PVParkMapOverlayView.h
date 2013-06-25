//
//  PVParkMapOverlayView.h
//  Park View
//
//  Created by sumantar on 25/06/13.
//  Copyright (c) 2013 Chris Wagner. All rights reserved.
//

#import <MapKit/MapKit.h>

@interface PVParkMapOverlayView : MKOverlayView

- (instancetype)initWithOverlay:(id<MKOverlay>)overlay overlayImage:(UIImage *)overlayImage;

@end
