# ROS2 Encryption System

A ROS2-based encryption and decryption system using Base64 encoding.

## Nodes
- publisher_node: Publishes original messages
- encryption_node: Encodes messages using Base64
- decryption_node: Decodes Base64 messages

## Topics
- original_message: Original text messages
- encrypted_message: Base64 encoded messages  
- decrypted_message: Decoded messages

## Build
colcon build --packages-select encryption_system
