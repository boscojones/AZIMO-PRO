#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> // Necessário para dlopen, dlsym, dlclose

// Define o tipo da função de assembly
typedef int32_t (*AssemblyFunc)(int32_t);

// Função para carregar a biblioteca e chamar a função Assembly
int32_t callAssemblyFunction(int32_t input) {
    // Determine o caminho da biblioteca dinâmica
    const char *libraryPath;
#if defined(_WIN32) || defined(_WIN64)
    libraryPath = "libassembly.dll"; // Para Windows
#else
    libraryPath = "libassembly.so"; // Para Linux/Unix
#endif

    // Carregar a biblioteca
    void *dylib = dlopen(libraryPath, RTLD_LAZY);
    if (!dylib) {
        fprintf(stderr, "Erro ao carregar a biblioteca: %s\n", dlerror());
        return -1;
    }

    // Procura a função na biblioteca
    AssemblyFunc assemblyFunction = (AssemblyFunc)dlsym(dylib, "assembly_function");
    if (!assemblyFunction) {
        fprintf(stderr, "Erro ao encontrar a função: %s\n", dlerror());
        dlclose(dylib);
        return -1;
    }

    // Chama a função Assembly com o valor desejado
    int32_t result = assemblyFunction(input);

    // Fecha a biblioteca
    dlclose(dylib);

    return result;
}

// Chamar a função com um valor de entrada
int main() {
    int32_t input = 10;
    int32_t result = callAssemblyFunction(input);
    printf("Resultado da função Assembly: %d\n", result);
    return 0;
}
