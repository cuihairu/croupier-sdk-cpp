# Croupier SDK (C++)

Work in progress. This module will provide a C++ SDK for Croupier to:
- Register local handlers (FunctionService) and interact with Agent
- Call functions via FunctionService (Core/Agent)

Build
```
cmake -S . -B build
cmake --build build -j
```

Run example
```
./build/croupier_example
```

Links
- Main project: https://github.com/cuihairu/croupier
- Go SDK (reference): https://github.com/cuihairu/croupier-sdk-go

Status
- Skeleton only; API and gRPC bindings will be added later via IDL generation.
