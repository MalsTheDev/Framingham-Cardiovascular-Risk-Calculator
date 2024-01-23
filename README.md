# Framingham Cardiovascular Risk Calculator

This C program is designed to calculate a cardiovascular risk score by analyzing medical information provided by the user. The goal is to assess the risk of cardiovascular issues using a recognized algorithm, such as the Framingham Risk Score.

 # Key Features

## Personalized Risk Assessment
The calculator dynamically computes and displays the risk based on user-input parameters. Results are stored in a "patients.txt" file for future reference.

## Risk Categorization
Each calculation not only provides the numerical risk but also categorizes it into levels such as low risk, moderate risk, or high risk, offering a comprehensive understanding of the potential cardiovascular threat.

## Patient History Retrieval
Users can conveniently search for a patient's information by their insurance number. The tool extracts and presents all previous risk scores from the "patients.txt" file, enabling a detailed overview of an individual's cardiovascular risk history.

## Advanced Analysis for Age 100 and Above
If there are at least 100 records, every time the code is used, it also report the average risk scores per age group.

## Parameters

**• Age** <br />
**• Gender** <br />
**• Total cholesterol levels** <br />
**• HDL cholesterol levels** <br />
**• Systolic blood pressure** <br />
**• Smoking status** <br />
**• Insurance number** <br />