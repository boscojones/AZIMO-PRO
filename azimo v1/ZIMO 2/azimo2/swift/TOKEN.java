import Foundation

enum Role: String {
    case system, user, assistant
}

struct Message {
    let role: Role
    let content: String
}

class Tokenizer {
    let numReservedSpecialTokens = 256
    let bosToken = "<|begin_of_text|>"
    let eosToken = "<|end_of_text|>"
    var specialTokens: [String: Int] = [:]
    
    init() {
        // Initialize special tokens
        specialTokens[bosToken] = 128000
        specialTokens[eosToken] = 128001
        // Add more tokens as needed
    }
    
    func encode(_ input: String, bos: Bool, eos: Bool) -> [Int] {
        var tokens = [Int]()
        
        if bos {
            tokens.append(specialTokens[bosToken] ?? 0)
        }
        
        // Simple tokenization by splitting words
        let words = input.split(separator: " ").map { String($0) }
        for word in words {
            // For simplicity, using a hash value for demonstration
            // Replace this with actual tokenization logic
            tokens.append(word.hashValue) 
        }
        
        if eos {
            tokens.append(specialTokens[eosToken] ?? 0)
        }
        
        return tokens
    }
    
    func decode(_ tokens: [Int]) -> String {
        // Simple decoding (not accurate)
        return tokens.map { String($0) }.joined(separator: " ")
    }
    
    func encodeMessage(_ message: Message) -> [Int] {
        var tokens = encode(message.role.rawValue, bos: true, eos: false)
        tokens += encode(message.content, bos: false, eos: true)
        return tokens
    }
    
    func encodeDialogPrompt(_ dialog: [Message]) -> [Int] {
        var tokens = encode(bosToken, bos: true, eos: false)
        for message in dialog {
            tokens += encodeMessage(message)
        }
        return tokens
    }
}

// Example usage
let tokenizer = Tokenizer()

// Testing encoding
let testMessage = Message(role: .user, content: "This is a test sentence.")
let encodedMessage = tokenizer.encodeMessage(testMessage)
print(encodedMessage)

// Testing decoding
let decodedMessage = tokenizer.decode(encodedMessage)
print(decodedMessage)

// Unit Tests
import XCTest

class TokenizerTests: XCTestCase {
    var tokenizer: Tokenizer!

    override func setUp() {
        super.setUp()
        tokenizer = Tokenizer()
    }

    func testEncode() {
        let tokens = tokenizer.encode("This is a test sentence.", bos: true, eos: true)
        XCTAssertEqual(tokens.first, 128000) // Check start token
        XCTAssertEqual(tokens.last, 128001) // Check end token
    }

    func testDecode() {
        let tokens = [128000, 2028, 374, 264, 1296, 11914, 13, 128001]
        let decodedString = tokenizer.decode(tokens)
        XCTAssertEqual(decodedString, "This is a test sentence.")
    }

    func testEncodeMessage() {
        let message = Message(role: .user, content: "This is a test sentence.")
        let encodedMessage = tokenizer.encodeMessage(message)
        XCTAssertTrue(encodedMessage.contains(128000)) // Message start
        XCTAssertTrue(encodedMessage.contains(128001)) // Message end
    }

    func testEncodeDialog() {
        let dialog: [Message] = [
            Message(role: .system, content: "This is a test sentence."),
            Message(role: .user, content: "This is a response.")
        ]
        let encodedDialog = tokenizer.encodeDialogPrompt(dialog)
        XCTAssertTrue(encodedDialog.contains(128000)) // Dialog start
    }
}
