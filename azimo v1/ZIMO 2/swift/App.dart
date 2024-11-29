import 'package:flutter/material.dart';

void main() {
  runApp(Tesla5001App());
}

class Tesla5001App extends StatelessWidget {
  final DateTime currentDate;

  Tesla5001App({Key? key}) 
    : currentDate = DateTime.now(), // Inicializa a data atual
      super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Tesla5001',
      home: IonControlView(currentDate: currentDate),
    );
  }
}

class IonControlView extends StatelessWidget {
  final DateTime currentDate;

  const IonControlView({Key? key, required this.currentDate}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Tesla5001'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Text(
              'Bem-vindo ao Tesla5001!',
              style: TextStyle(fontSize: 24),
            ),
            const SizedBox(height: 20),
            Text(
              'Data atual: ${currentDate.toLocal()}',
              style: const TextStyle(fontSize: 18),
            ),
          ],
        ),
      ),
    );
  }
}
