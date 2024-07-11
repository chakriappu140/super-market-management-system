# 📦 Inventory Management System

## Overview

This Inventory Management System is a simple C++ console application designed to manage and maintain a product inventory. The application allows users to add, update, display, search, and delete products from the inventory. Additionally, it provides functionalities for billing, where users can add items to a cart and print the bill.

## Features

1. **➕ Add Product**: Add new products to the inventory.
2. **🔄 Update Product**: Update the quantity or price of existing products.
3. **📋 Display Inventory**: Display all products in the inventory with their details.
4. **🔍 Search Product**: Search for a specific product in the inventory.
5. **🗑️ Delete Product**: Remove a product from the inventory.
6. **💾 Save and Load Inventory**: Save the current inventory to a file and load it from a file.
7. **🛒 Billing**: Add products to a cart and print the bill for the purchased items.

## Requirements

- 🛠️ C++ Compiler
- 📚 Standard Template Library (STL)

## How to Use

### Compile and Run

1. **🖥️ Compile**: 
   ```sh
   g++ -o inventory_management main.cpp
   ```

2. **▶️ Run**:
   ```sh
   ./inventory_management
   ```

### Main Menu

After running the program, you will see the main menu with the following options:

1. **Manage Inventory**
2. **Billing**
3. **Exit**

### Manage Inventory

Select option `1` from the main menu to manage the inventory. The sub-menu will provide the following options:

1. **Add a product**
2. **Update a product**
3. **Display the inventory**
4. **Search for a product**
5. **Delete a product**
6. **Save and exit**

### Billing

Select option `2` from the main menu to enter the billing section. The sub-menu will provide the following options:

1. **Add items to cart**
2. **Print bill**
3. **Exit**

### Exit

Select option `3` from the main menu to exit the program.

## File Handling

- **📥 Loading Inventory**: The inventory is loaded from `inv.txt` file at the start of the program.
- **📤 Saving Inventory**: The inventory is saved to `inv.txt` file upon selecting the "Save and exit" option in the Manage Inventory menu or when exiting the billing section.

## Code Structure

The project consists of the following classes:

1. **🧩 item**: Abstract base class for items.
2. **📦 product**: Inherits from `item` and represents a product in the inventory.
3. **📂 inventory**: Manages the collection of products.
4. **🛒 cart**: Represents the shopping cart for billing.

## Sample `inv.txt` File

The `inv.txt` file should have the following format:

```
product_name,quantity,price
```

Example:

```
Apple,50,0.50
Banana,100,0.30
Orange,75,0.60
```

## 📜 License

This project is licensed under the MIT License.

## 🤝 Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests.

---

### Note

This application is a simple implementation intended for educational purposes and may not cover all edge cases or real-world scenarios. For more robust solutions, consider using a database and more advanced error handling techniques.
