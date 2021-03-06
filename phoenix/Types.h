//
//  Types.h
//
//  Created by Gregory Casamento on 10/20/14.
//

#import <Foundation/Foundation.h>

@class ASTNode;
@class ExpressionList;

enum {
    TYPE_STRING = 1,
    TYPE_BOOLEAN, TYPE_NUMBER, TYPE_ARRAY, TYPE_DICTIONARY,
    TYPE_TUPLE,
    TYPE_FUNCTION,
    TYPE_CLASS,
    TYPE_STRUCT,
    TYPE_VOID,
    TYPE_UNKNOWN
};
typedef NSUInteger SwiftType;

// GenericType...
@interface GenericType : NSObject
@property (nonatomic,assign) SwiftType type;
@property (nonatomic,assign) BOOL optional;
- (id)initWithType: (SwiftType)type;
- (GenericType *) operate: (NSString *)op
                         : (GenericType *)other;
- (NSString *) customBinaryOperator: (ASTNode *)myNode
                                   : (NSString *)op
                                   : (ASTNode *)otherNode;
+ (GenericType *) fromTypeIdentifier: (NSString *)name;
@end

// IndirectionType...
@interface IndirectionType : GenericType
@property (nonatomic, retain) GenericType *pointer;
- (id) initWithPointer: (GenericType *)pointer;
- (void) update: (GenericType *)pointer;
@end

// TupleType...
@interface TupleType: GenericType
@property (nonatomic, retain) NSMutableArray *names;
@property (nonatomic, retain) NSMutableArray *types;
- (id) initWithList: (ASTNode *)list;
- (void) addType: (NSString *)name
                : (GenericType *)type;
- (GenericType *) getTypeForIndex:(int)index;
@end

// ArrayType...
@interface ArrayType: GenericType
@property (nonatomic, retain) GenericType *innerType;
- (id) initWithInnerType: (GenericType *)innerType;
@end

// DictionaryType...
@interface DictionaryType: GenericType
@property (nonatomic, retain) GenericType *innerType;
- (id) initWithInnerType: (GenericType *)innerType;
@end

// FunctionType...
@interface FunctionType: GenericType
@property (nonatomic, retain) GenericType *returnType;
@property (nonatomic, retain) NSMutableArray *argumentTypes;
- (id) initWithArgumentTypes: (NSMutableArray *)argumentTypes
                  returnType: (GenericType *)returnType;
- (id) initWithArgsType:(GenericType *)argsType
             returnType:(GenericType *)returnType;
@end
