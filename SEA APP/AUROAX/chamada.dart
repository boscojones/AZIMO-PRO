import 'dart:ffi'; // FFI
import 'dart:io';  // Platform

typedef AssemblyFunc = Int32 Function(Int32);
typedef Assembly = int Function(int);

void main() {
  // Carregar a biblioteca compilada em Assembly
  final dylib = Platform.isWindows
      ? DynamicLibrary.open('libassembly.dll')
      : DynamicLibrary.open('libassembly.so');

  final Assembly assemblyFunction = dylib
      .lookup<NativeFunction<AssemblyFunc>>('assembly_function')
      .asFunction();
  
  // Chamar a função Assembly com o valor desejado
  int result = assemblyFunction(10); // Exemplo de entrada
  print('Resultado da função Assembly: $result');
}
