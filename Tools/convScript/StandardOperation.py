
import OperationRegistry;
import Operations;

groupAll = Operations.GroupingOperation("all");

OperationRegistry.registerOperation(groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgcos", "osgcos", "osgCos"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgsin", "osgsin", "osgSin"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgtan", "osgtan", "osgTan"), groupAll);

OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgacos", "osgacos", "osgACos"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgasin", "osgasin", "osgASin"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgatan", "osgatan", "osgATan"), groupAll);

OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgasb", "osgabs", "osgAbs"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgpow", "osgpow", "osgPow"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osglog", "osglog", "osgLog"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgexp", "osgexp", "osgExp"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgfloor", "osgfloor", "osgFloor"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgceil", "osgceil", "osgCeil"), groupAll);
OperationRegistry.registerOperation(Operations.SimpleReplaceOperation("osgfinite", "osgfinite", "osgFinite"), groupAll);
