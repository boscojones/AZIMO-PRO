import 'dart:ffi'; // Biblioteca FFI para chamadas nativas
import 'dart:io'; // Para determinar o SO

typedef AssemblyFunctionNative = Int32 Function(Int32);
typedef AssemblyFunction = int Function(int);

class HoloFiKernel {
  late DynamicLibrary _library;
  late AssemblyFunction _assemblyFunction;

  HoloFiKernel() {
    // Determina o caminho da biblioteca nativa
    String libraryPath;
    if (Platform.isWindows) {
      libraryPath = 'libassembly.dll';
    } else {
      libraryPath = 'libassembly.so';
    }

    // Carrega a biblioteca
    _library = DynamicLibrary.open(libraryPath);

    // Mapeia a função Assembly
    _assemblyFunction = _library
        .lookup<NativeFunction<AssemblyFunctionNative>>('assembly_function')
        .asFunction();
  }

  /// Chama a função Assembly com um valor de entrada
  int callAssemblyFunction(int input) {
    return _assemblyFunction(input);
  }
}

void main() {
  final kernel = HoloFiKernel();

  const int input = 10;
  final result = kernel.callAssemblyFunction(input);

  print('Resultado da função Assembly: $result');
}
