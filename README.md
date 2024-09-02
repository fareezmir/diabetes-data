# Diabetes Data Analysis

This repository contains the source code and data files for a data science project that analyzes the prevalence of diabetes in Canada, specifically focusing on the four most populous provinces: Ontario, Quebec, British Columbia, and Alberta. The project involves reading data from a text file, performing calculations, and outputting results on various statistics related to diabetes.

## Overview

The project uses C programming to perform computations on data collected by Statistics Canada. The key focus areas include:

1. **Provincial Averages**: Calculates the average percentage of the population diagnosed with diabetes in each province.

2. **National Average**: Computes the overall average percentage of the population diagnosed with diabetes across Canada (excluding territories).

3. **Yearly Averages**: Determines the yearly average percentage of diabetes for each province and Canada as a whole from 2015 to 2021.

4. **Age Group Averages**: Analyzes the average percentage of diabetes among different age groups (35-49, 50-64, 65+) for each province and nationwide.

5. **Highest and Lowest Diabetes Rates**: Identifies the provinces with the highest and lowest diabetes percentages and highlights the specific years where these peaks occurred.

6. **Above/Below National Average**: Indicates which provinces have diabetes rates above or below the national average.

## Files Included

- **`main.c`**: The C program that processes the diabetes data and performs all calculations.
- **`statscan_diabetes.txt`**: The dataset file containing diabetes statistics used by the program.
- **`Diabetes in Canada.pdf`**: A report detailing the analysis, results, and insights gained from the data processing.
  
## How to Run

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/diabetes-data.git
    ```

2. **Compile the C program**:
    ```bash
    gcc -o diabetes_analysis main.c
    ```

3. **Run the compiled program**:
    ```bash
    ./diabetes_analysis
    ```

The program will output the calculated statistics directly to the console.

## Calculations Performed

The following computations are made by the program:

1. **Provincial Averages**: Averages the percentage of the population diagnosed with diabetes for Ontario, Quebec, British Columbia, and Alberta.

2. **National Average**: Calculates the national average (Canada excluding territories) for all years and age groups.

3. **Yearly Averages**: Produces yearly averages from 2015 to 2021 for each province and Canada as a whole.

4. **Age Group Averages**: Computes averages for each age group (35-49, 50-64, 65+) for each province and nationwide.

5. **Highest/Lowest Diabetes Rates**: Identifies the province with the highest and lowest diabetes rates and the years when these occurred.

6. **Comparison to National Average**: Lists provinces with diabetes rates above and below the national average.

## Future Improvements

- **Graphical Representation**: Implementing graphical outputs using GNUPlot for better visualization of data trends.
- **Enhanced Data Analysis**: Adding more in-depth statistical analysis and possibly machine learning predictions based on historical data.

---

Feel free to explore the code! Thanks for reading!
