//
//  WebSocket.h
//
//  Originally created for Zimt by Esad Hajdarevic on 2/14/10.
//  Copyright 2010 OpenResearch Software Development OG. All rights reserved.
//
//  Erich Ocean made the code more generic.
//
//  Tobias Rodäbel implemented support for draft-hixie-thewebsocketprotocol-76.
//

#import <Foundation/Foundation.h>

@class AsyncSocket;
@class WebSocket;

@protocol WebSocketDelegate<NSObject>
@optional
- (void)webSocket:(WebSocket *)webSocket didFailWithError:(NSError *)error;
- (void)webSocketDidOpen:(WebSocket *)webSocket;
- (void)webSocketDidClose:(WebSocket *)webSocket;
- (void)webSocket:(WebSocket *)webSocket didReceiveTextMessage:(NSString *)message;
- (void)webSocket:(WebSocket *)webSocket didReceiveBinaryMessage:(NSData *)message;
- (void)webSocketDidSendMessage:(WebSocket *)webSocket;
- (void)webSocketDidSecure:(WebSocket *)webSocket;

// Deprecated, but will work in place of |webSocket:didReceiveTextMessage:|
// if you do not implement that method.
- (void)webSocket:(WebSocket *)webSocket didReceiveMessage:(NSString *)message;
@end

typedef enum {
    WebSocketStateDisconnected,
    WebSocketStateConnecting,
    WebSocketStateConnected,
} WebSocketState;

@interface WebSocket : NSObject {
    AsyncSocket *socket;
}

@property(nonatomic,assign) id<WebSocketDelegate> delegate;
@property(nonatomic,readonly) NSURL *url;
@property(nonatomic,retain) NSString *origin;
@property(nonatomic,readonly) WebSocketState state;
@property(nonatomic,readonly) BOOL secure;
@property(nonatomic,retain) NSArray *runLoopModes;

+ (id)webSocketWithURLString:(NSString *)urlString delegate:(id<WebSocketDelegate>)delegate;
- (id)initWithURLString:(NSString *)urlString delegate:(id<WebSocketDelegate>)delegate;

- (void)open;
- (void)close;
- (void)send:(NSString*)message;

// Deprecated:
- (BOOL)connected; // Returns state==WebSocketStateConnected

@end

enum {
    WebSocketErrorConnectionFailed = 1,
    WebSocketErrorHandshakeFailed = 2
};

extern NSString * const WebSocketException;
extern NSString * const WebSocketErrorDomain;
