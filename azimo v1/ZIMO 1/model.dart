import 'dart:math';

class RMSNorm {
  final int dim;
  final double eps;
  List<double> weights;

  RMSNorm(this.dim, {this.eps = 1e-6}) : weights = List.filled(dim, 1.0);

  List<double> _norm(List<double> x) {
    final meanSquare = x.map((e) => e * e).reduce((a, b) => a + b) / x.length;
    final scale = 1.0 / sqrt(meanSquare + eps);
    return x.map((e) => e * scale).toList();
  }

  List<double> forward(List<double> x) {
    final normalized = _norm(x);
    return List.generate(dim, (i) => normalized[i] * weights[i]);
  }
}

class FeedForward {
  final int inputDim;
  final int hiddenDim;
  final int outputDim;

  FeedForward(this.inputDim, this.hiddenDim, this.outputDim);

  List<double> forward(List<double> x) {
    // Implementar transformação linear + ativação
    return x.map((e) => e > 0 ? e : 0).toList(); // Exemplo simplificado
  }
}

class TransformerBlock {
  final int dim;
  final RMSNorm attentionNorm;
  final FeedForward feedForward;

  TransformerBlock(this.dim, int hiddenDim)
      : attentionNorm = RMSNorm(dim),
        feedForward = FeedForward(dim, hiddenDim, dim);

  List<double> forward(List<double> x) {
    final normed = attentionNorm.forward(x);
    final attended = feedForward.forward(normed);
    return attended;
  }
}

void main() {
  final transformerBlock = TransformerBlock(256, 512);

  final input = List.generate(256, (i) => Random().nextDouble());
  final output = transformerBlock.forward(input);

  print(output);
}
