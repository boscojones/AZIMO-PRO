import Foundation

let compileCommand = "gcc" // Compile command
let outputName = "output_program" // Name of the final program
let terminalCommand = "./" // Command to execute the program

// Function to compile all .c files in the current directory
func compileAllCFiles() {
    var compileCmd = "\(compileCommand) -o \(outputName) " // Buffer for the compile command

    // Get the current directory
    let fileManager = FileManager.default
    do {
        let currentPath = fileManager.currentDirectoryPath
        let items = try fileManager.contentsOfDirectory(atPath: currentPath)

        // List all files in the current directory
        for item in items {
            // Check for .c files
            if item.hasSuffix(".c") {
                compileCmd += "\(item) "
            }
        }

        // Check if there are files to compile
        if compileCmd == "\(compileCommand) -o \(outputName) " {
            print("Nenhum arquivo .c encontrado para compilar.")
            return
        }

        // Execute the compile command
        print("Compiling with command: \(compileCmd)")
        let compileResult = system(compileCmd)

        if compileResult != 0 {
            print("Compilation failed.")
            return
        }

        print("Compilation successful!")
    } catch {
        print("Error accessing directory: \(error)")
    }
}

// Function to execute the compiled program
func runProgram() {
    let runCmd = "\(terminalCommand)\(outputName)"
    
    // Execute the program
    print("Executing the program: \(runCmd)")
    let runResult = system(runCmd)

    if runResult != 0 {
        print("Execution failed.")
    } else {
        print("Program executed successfully.")
    }
}

// Main function
func main() {
    compileAllCFiles()  // Compile all .c files
    runProgram()        // Execute the compiled program
}

// Call the main function
main()
