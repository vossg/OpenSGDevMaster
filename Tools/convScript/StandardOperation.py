
import OperationRegistry;
import Operations;

groupAll = Operations.GroupingOperation("All");
groupBaseFuncRename = Operations.GroupingOperation("BaseFuncRename");


OperationRegistry.registerOperation(groupAll);
OperationRegistry.registerOperation(groupBaseFuncRename);


OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgsqrt", "osgsqrt", "osgSqrt"), groupBaseFuncRename);

OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgcos", "osgcos", "osgCos"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgsin", "osgsin", "osgSin"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgtan", "osgtan", "osgTan"), groupBaseFuncRename);

OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgacos", "osgacos", "osgACos"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgasin", "osgasin", "osgASin"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgatan", "osgatan", "osgATan"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgatan2", "osgatan2", "osgATan2"), groupBaseFuncRename);

OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgasb", "osgabs", "osgAbs"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgpow", "osgpow", "osgPow"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osglog", "osglog", "osgLog"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgexp", "osgexp", "osgExp"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgfloor", "osgfloor", "osgFloor"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgceil", "osgceil", "osgCeil"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgfinite", "osgfinite", "osgFinite"), groupBaseFuncRename);

OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgdegree2rad", "osgdegree2rad", "osgDegree2Rad"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgrad2degree", "osgrad2degree", "osgRad2Degree"), groupBaseFuncRename);

OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgispower2", "osgispower2", "osgIsPower2"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgnextpower2", "osgnextpower2", "osgNextPower2"), groupBaseFuncRename);

OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgsleep", "osgsleep", "osgSleep"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgrand", "osgrand", "osgRand"), groupBaseFuncRename);

OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("stringDup", "stringDup", "osgStringDup"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("stringcpy", "stringcpy", "osgStringCopy"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("stringncmp", "stringncmp", "osgStringNCmp"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("stringlen", "stringlen", "osgStringLen"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("stringcmp", "stringcmp", "osgStringCmp"), groupBaseFuncRename);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("stringcasecmp", "stringcasecmp", "osgStringCaseCmp"), groupBaseFuncRename);


groupAll.addOp("BaseFuncRename");