//
//  platform/mac/Utility_mac.cpp
//  pTK
//
//  Created by Robin Gustafsson on 2021-02-14.
//

#ifndef PTK_PLATFORM_MAC_ULILITY_HPP
#define PTK_PLATFORM_MAC_ULILITY_HPP

// macOS Headers
#import <Cocoa/Cocoa.h>

@implementation NSString (cppstring_additions)

#if TARGET_RT_BIG_ENDIAN
const NSStringEncoding kEncoding_wchar_t = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingUTF32BE);
#else
const NSStringEncoding kEncoding_wchar_t = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingUTF32LE);
#endif

+ (NSString*)stringWithwstring:(const std::wstring&)ws
{
    const char* data = reinterpret_cast<const char*>(ws.data());
    unsigned size = static_cast<unsigned>(ws.size() * sizeof(wchar_t));

    NSString* result = [[NSString alloc] initWithBytes:data length:size encoding:kEncoding_wchar_t];
    return result;
}
+ (NSString*)stringWithstring:(const std::string&)s
{
    NSString* result = [[NSString alloc] initWithUTF8String:s.c_str()];
    return result;
}

- (std::wstring)getwstring
{
    NSData* asData = [self dataUsingEncoding:kEncoding_wchar_t];
    return std::wstring(static_cast<const wchar_t*>([asData bytes]), [asData length] / sizeof(wchar_t));
}
- (std::string)getstring
{
    return [self UTF8String];
}

@end

#endif // PTK_PLATFORM_MAC_ULILITY_HPP
