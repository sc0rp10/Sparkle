//
//  SPUStandardUpdaterController.h
//  Sparkle
//
//  Created by Mayur Pawashe on 2/28/16.
//  Copyright © 2016 Sparkle Project. All rights reserved.
//

#if __has_feature(modules)
#if __has_warning("-Watimport-in-framework-header")
#pragma clang diagnostic ignored "-Watimport-in-framework-header"
#endif
@import Foundation;
#else
#import <Foundation/Foundation.h>
#endif
#import <Sparkle/SUExport.h>

NS_ASSUME_NONNULL_BEGIN

@class SPUUpdater;
@class SPUStandardUserDriver;
@class NSMenuItem;
@protocol SPUUserDriver, SPUUpdaterDelegate, SPUStandardUserDriverDelegate;

/*!
 A controller class that instantiates a SPUUpdater and allows binding UI to it.
 
 This class can be instantiated in a nib or created programatically using initWithUpdaterDelegate:userDriverDelegate: or initWithStartingUpdater:updaterDelegate:userDriverDelegate:.
 
 The controller's updater targets the application's main bundle and uses Sparkle's standard user interface.
 Typically, this class is used by sticking it as a custom NSObject subclass in an Interface Builder nib (probably in MainMenu) but it works well programatically too.
 
 The controller creates an SPUUpdater instance and allows hooking up the check for updates action and menu item validation. It also allows hooking
 up the updater's and user driver's delegates.
 
 If you need more control over what bundle you want to update or you want to provide a custom user interface (via SPUUserDriver), please use SPUUpdater directly instead.
  */
SU_EXPORT @interface SPUStandardUpdaterController : NSObject

/*!
 Interface builder outlet for the updater's delegate.
 
 This property should only be set using Interface Builder by creating a connection using the outlet.
 */
@property (nonatomic, weak, nullable) IBOutlet id<SPUUpdaterDelegate> updaterDelegate;

/*!
 Interface builder outlet for the user driver's delegate.
 
 This property should only be set using Interface Builder by creating a connection using the outlet.
 */
@property (nonatomic, weak, nullable) IBOutlet id<SPUStandardUserDriverDelegate> userDriverDelegate;

/*!
 Accessible property for the updater. Some properties on the updater can be binded via KVO
 
 When instantiated from a nib, don't perform update checks before the application has finished launching in a MainMenu nib (i.e applicationDidFinishLaunching:) or before the corresponding window/view controller has been loaded (i.e, windowDidLoad or viewDidLoad). The updater is not guaranteed to be started yet before these points.
 */
@property (nonatomic, readonly) SPUUpdater *updater;

/*!
 Accessible property for the updater's user driver.
 */
@property (nonatomic, readonly) SPUStandardUserDriver *userDriver;

/*!
 Create a new SPUStandardUpdaterController from a nib.
 
 You cannot call this initializer directly. You must instantiate a SPUStandardUpdaterController inside of a nib (typically the MainMenu nib) to use it.
 
 To create a SPUStandardUpdaterController programatically, use initWithUpdaterDelegate:userDriverDelegate: or initWithStartingUpdater:updaterDelegate:userDriverDelegate: instead.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 Create a new SPUStandardUpdaterController programmatically.
 
 The updater is started automatically. See -[SPUStandardUpdaterController startUpdater]  for more information.
 */
- (instancetype)initWithUpdaterDelegate:(nullable id<SPUUpdaterDelegate>)updaterDelegate userDriverDelegate:(nullable id<SPUStandardUserDriverDelegate>)userDriverDelegate;

/*!
 Create a new SPUStandardUpdaterController programmatically allowing you to specify whether or not to start the updater immediately.
 
 You can specify whether or not you want to start the updater immediately. If you do not start the updater, you
 must invoke -[SPUStandardUpdaterController startUpdater] at a later time to start it.
 */
- (instancetype)initWithStartingUpdater:(BOOL)startUpdater updaterDelegate:(nullable id<SPUUpdaterDelegate>)updaterDelegate userDriverDelegate:(nullable id<SPUStandardUserDriverDelegate>)userDriverDelegate;

/*!
 Starts the updater if it has not already been started.
 
 You should only call this method yourself if you opted out of starting the updater on initialization.
 Hence, do not call this yourself if you are instantiating this controller from a nib.
 
 This invokes  -[SPUUpdater startUpdater:]. If the application is misconfigured with Sparkle, an error is logged and an alert is shown to the user (after a few seconds) to contact the developer.
 If you want more control over this behavior, you can create your own SPUUpdater instead.
 */
- (void)startUpdater;

/*!
 Explicitly checks for updates and displays a progress dialog while doing so.
 
 This method is meant for a main menu item.
 Connect any menu item to this action in Interface Builder,
 and Sparkle will check for updates and report back its findings verbosely
 when it is invoked.
 
 This action checks updates by invoking -[SPUUpdater checkForUpdates]
 */
- (IBAction)checkForUpdates:(nullable id)sender;

/*!
 Validates if the menu item for checkForUpdates: can be invoked or not
 
 This validates the menu item by checking -SPUUpdater.canCheckForUpdates
 */
- (BOOL)validateMenuItem:(NSMenuItem *)item;

@end

NS_ASSUME_NONNULL_END
