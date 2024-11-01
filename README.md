# LNS-Based MAC Unit Implementation

This repository contains the implementation of a Multiply-Accumulate (MAC) unit designed using a **Logarithmic Number System (LNS)** to optimize performance in hardware accelerators, particularly for **deep neural networks (DNNs)**. The design leverages Xilinx’s Vitis HLS for synthesis and targets FPGA platforms, such as Artix, Virtex, and Kintex. This approach aims to reduce computational costs, resource usage, and power consumption, making it suitable for high-performance, low-power applications.

## Features

- **Multi-Base LNS Representation**: Implements a hardware-efficient multi-base LNS that supports variable bases with fractional exponents, enabling optimized computation for different neural network models.
- **FPGA-Oriented Design**: Tailored for synthesis with Vitis HLS, allowing compatibility with various FPGA families, particularly from Xilinx.
- **LUT-Based Remainder Management**: The LNS exponent is decomposed into a quotient and remainder, where the remainder is managed by a precomputed lookup table (LUT). This approach minimizes memory requirements while maintaining computational efficiency.
- **Quantization-Aware Training Compatibility**: The MAC unit’s design supports quantized neural network training, enabling efficient training and inference in low-precision formats without sacrificing model accuracy.

## Repository Structure

- `LNS_datatype.h`: Contains definitions and data structures for the multi-base logarithmic number representation, including functions to handle conversion between logarithmic and integer formats.
- `mac.h` and `mac.cpp`: Define and implement the Multiply-Accumulate (MAC) unit using the LNS-based arithmetic approach. The MAC unit leverages simplified arithmetic operations to reduce hardware complexity, with multiplication achieved through additions of logarithmic values.
- `mul_unit.h` and `mul_unit.cpp`: Define and implement the multiplication operation within the LNS, using LUT-based remainder handling for exponent addition, which enhances both speed and resource efficiency.
- `add_unit.h` and `add_unit.cpp`: Define and implement addition operations, accommodating LNS-specific challenges where additions require converting logarithmic values back to integer format for precise accumulation.

## LNS-Based Arithmetic Operations

This design approach utilizes an **LUT-based conversion method** that divides the exponent into:
- **Quotient**: Handled via bit-shifting to scale values without multipliers.
- **Remainder**: Managed through a LUT with precomputed values of \( 2^{p_{i_r}} \), which reduces the need for complex exponential calculations and ensures low-latency operations.

By storing only the remainder values in the LUT, memory requirements are minimized while maintaining accuracy. This decomposition provides a highly efficient solution for LNS arithmetic in FPGA hardware.

## Usage

1. **Requirements**:
   - Xilinx Vitis HLS
   - Compatible FPGA hardware (e.g., Artix, Virtex, Kintex series)

2. **Compilation**:
   - The code is structured for synthesis with Vitis HLS. Open the project in Vitis HLS and specify the target FPGA for synthesis.

3. **Testing**:
   - Run the provided testbenches within Vitis HLS to verify functionality, resource utilization, and performance metrics (e.g., FF, LUT, DSP usage).

## Performance and Trade-offs

The MAC unit has been evaluated across multiple Xilinx FPGA families. Key performance metrics include:
- **Resource Utilization**: Analysis of flip-flops (FF), lookup tables (LUT), and DSP blocks.
- **Latency and Power Consumption**: Optimized for low-power applications without sacrificing computation speed.
- **Precision and Quantization Flexibility**: Supports varying levels of quantization, enabling compatibility with quantization-aware training and inference processes.

## Applications

This LNS-based MAC unit is particularly suitable for:
- **Deep Neural Network Acceleration**: Efficiently performs MAC operations with low power consumption.
- **Digital Signal Processing**: Suitable for high-throughput, low-latency DSP applications on FPGAs.
- **Embedded Machine Learning**: Supports low-precision neural network models, ideal for resource-constrained hardware.

## Future Work

Further improvements could include:
- Expanding LUT-based handling to other operations for additional efficiency.
- Adapting the design for broader FPGA families and exploring compatibility with ASICs.
- Exploring adaptive quantization techniques to further improve accuracy in quantized training scenarios.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
