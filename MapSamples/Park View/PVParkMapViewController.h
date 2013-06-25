#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

@interface PVParkMapViewController : UIViewController <MKMapViewDelegate>

@property (weak, nonatomic) IBOutlet UISegmentedControl *mapTypeSegmentedControl;

- (IBAction)mapTypeChanged:(id)sender;
@property (strong, nonatomic) IBOutlet MKMapView *mapView;

@end
