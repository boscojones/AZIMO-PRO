import 'dart:convert';
import 'dart:io';
import 'package:shelf/shelf.dart';
import 'package:shelf/shelf_io.dart' as shelf_io;
import 'package:shelf_router/shelf_router.dart';
import 'package:flutter/material.dart';

class RequestData {
  final String message;

  RequestData(this.message);

  factory RequestData.fromJson(Map<String, dynamic> json) {
    return RequestData(json['message']);
  }
}

class ResponseData {
  final String response;

  ResponseData(this.response);

  Map<String, dynamic> toJson() {
    return {'response': response};
  }
}

Future<Response> processRequest(Request request) async {
  // Parse the incoming JSON request
  final requestBody = await request.readAsString();
  final Map<String, dynamic> jsonData = jsonDecode(requestBody);
  
  RequestData reqData;
  try {
    reqData = RequestData.fromJson(jsonData);
  } catch (e) {
    return Response(HttpStatus.badRequest, body: jsonEncode({'response': 'Invalid request'}));
  }

  // Execute a command in the shell
  ProcessResult result;
  try {
    result = await Process.run('drake', ['your_command_here', reqData.message]);
  } catch (e) {
    return Response(HttpStatus.internalServerError, body: jsonEncode({'response': 'Error executing command'}));
  }

  final output = result.stdout.toString().trim();
  final response = output.isEmpty ? 'Desculpe, não consegui processar sua solicitação.' : output;

  return Response.ok(jsonEncode(ResponseData(response).toJson()), headers: {'Content-Type': 'application/json'});
}

void main() async {
  // Start the HTTP server
  final router = Router();
  router.post('/ask', processRequest);

  // Serve static files (if needed, adjust the path)
  final handler = const Pipeline().addMiddleware(logRequests()).addHandler(router);

  // Start the server
  final port = 8080;
  final server = await shelf_io.serve(handler, InternetAddress.anyIPv4, port);
  print('Server running on localhost
