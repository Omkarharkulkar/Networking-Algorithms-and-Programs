#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the parity bit
int calculateParityBit(const vector<int>& data, int startIndex, int stepSize) 
{
    int parity = 0;
    for (int i = startIndex; i < data.size(); i += stepSize) 
	{
        if (data[i] == 1)
            parity ^= 1;
    }
    return parity;
}

// Function to detect and correct the single-bit error
bool detectAndCorrectError(vector<int>& receivedData) 
{
    int parityIndices[] = {0, 1, 3, 7}; // Indices of parity bits in Hamming code
    int errorIndex = 0;

    // Calculate the parity bits
    vector<int> parityBits;
    for (int i = 0; i < sizeof(parityIndices) / sizeof(int); i++) 
	{
        int parity = calculateParityBit(receivedData, parityIndices[i], static_cast<int>(pow(2.0, i)));
        parityBits.push_back(parity);
    }

    // Check for errors and correct if needed
    for (int i = 0; i < parityBits.size(); i++) 
	{
        if (parityBits[i] != receivedData[parityIndices[i]]) 
		{
            errorIndex += static_cast<int>(pow(2.0, i));
        }
    }

    if (errorIndex != 0) 
	{
        // Error detected
        receivedData[errorIndex - 1] ^= 1; // Correct the error bit
        return true;
    }

    return false;
}

int main() 
{
    int dataLength;
    cout << "Enter the length of the data: ";
    cin >> dataLength;

    vector<int> data(dataLength);

    cout << "Enter the data bits (0 or 1) one by one:\n";
    for (int i = 0; i < dataLength; i++) 
	{
        cin >> data[i];
    }

    // Calculate the number of parity bits required
    int numParityBits = 0;
    while (static_cast<int>(pow(2.0, numParityBits)) < dataLength + numParityBits + 1) 
	{
        numParityBits++;
    }

    // Insert placeholder values for parity bits
    vector<int> encodedData(dataLength + numParityBits);
    int dataIndex = 0;
    int parityIndex = 0;

    for (int i = 0; i < encodedData.size(); i++) 
	{
        if (i + 1 == static_cast<int>(pow(2.0, parityIndex))) 
		{
            encodedData[i] = 0;
            parityIndex++;
        } 
		else 
		{
            encodedData[i] = data[dataIndex];
            dataIndex++;
        }
    }

    // Calculate the parity bits
    for (int i = 0; i < numParityBits; i++) 
	{
        encodedData[static_cast<int>(pow(2.0, i)) - 1] = calculateParityBit(encodedData, i, static_cast<int>(pow(2.0, i)));
    }

    cout << "Enter the received data bits (0 or 1) one by one:\n";
    for (int i = 0; i < encodedData.size(); i++) 
	{
        cin >> encodedData[i];
    }

    // Check if there is an error and correct it
    if (detectAndCorrectError(encodedData)) 
	{
        cout << "Error detected and corrected. The corrected data is:\n";
        for (int i = 0; i < dataLength; i++) 
		{
            cout << encodedData[i] << " ";
        }
        cout << endl;
    } 
	else 
	{
        cout << "No error detected in the received data.\n";
    }

    return 0;
}

