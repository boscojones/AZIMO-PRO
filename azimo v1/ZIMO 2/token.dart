import 'dart:convert';

class Tokenizer {
  final Map<String, int> specialTokens = {
    "<|begin_of_text|>": 128000,
    "<|end_of_text|>": 128001,
    "<|start_header_id|>": 128006,
    "<|end_header_id|>": 128007,
    "<|eot_id|>": 128009,
  };

  // Tokenizar entrada simples
  List<int> encode(String input, {bool bos = false, bool eos = false}) {
    List<int> tokens = utf8.encode(input);

    if (bos) tokens.insert(0, specialTokens["<|begin_of_text|>"]!);
    if (eos) tokens.add(specialTokens["<|end_of_text|>"]!);

    return tokens;
  }

  // Decodificar tokens
  String decode(List<int> tokens) {
    return utf8.decode(tokens);
  }
}

class ChatFormat {
  final Tokenizer tokenizer;

  ChatFormat(this.tokenizer);

  // Codifica uma mensagem única
  List<int> encodeMessage(Map<String, String> message) {
    List<int> tokens = [
      tokenizer.specialTokens["<|start_header_id|>"]!,
      ...utf8.encode(message["role"] ?? ""),
      tokenizer.specialTokens["<|end_header_id|>"]!,
      271, // Representa "\n\n"
      ...utf8.encode(message["content"] ?? ""),
      tokenizer.specialTokens["<|eot_id|>"]!,
    ];
    return tokens;
  }

  // Codifica um diálogo inteiro
  List<int> encodeDialogPrompt(List<Map<String, String>> dialog) {
    List<int> tokens = [tokenizer.specialTokens["<|begin_of_text|>"]!];

    for (var message in dialog) {
      tokens.addAll(encodeMessage(message));
    }

    return tokens;
  }
}
class LearningModule {
  final Map<String, int> tokenFrequency = {};

  void updateFrequency(String input) {
    var tokens = utf8.encode(input);
    for (var token in tokens) {
      tokenFrequency[token.toString()] =
          (tokenFrequency[token.toString()] ?? 0) + 1;
    }
  }
}
