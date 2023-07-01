#include <iostream>
#include <vector>

using namespace std;

// Function to perform CRC division
vector<int> performCRC(const vector<int>& data, const vector<int>& generator) 
{
    vector<int> dividend(data);
    int generatorSize = generator.size();

    for (int i = 0; i <= dividend.size() - generatorSize; i++) 
	{
        if (dividend[i] == 1) 
		{
            for (int j = 0; j < generatorSize; j++) 
			{
                dividend[i + j] = (dividend[i + j] + generator[j]) % 2;
            }
        }
    }

    return dividend;
}

// Function to detect and correct the single-bit error
bool detectAndCorrectError(vector<int>& receivedData, const vector<int>& generator) 
{
    vector<int> remainder = performCRC(receivedData, generator);

    // Check if there is an error
    for (int i = 0; i < remainder.size(); i++) 
	{
        if (remainder[i] != 0) 
		{
            // Error detected
            int errorIndex = receivedData.size() - generator.size() + i;
            receivedData[errorIndex] = (receivedData[errorIndex] + 1) % 2; // Correct the error
            return true;
        }
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

    int generatorSize;
    cout << "Enter the size of the generator: ";
    cin >> generatorSize;

    vector<int> generator(generatorSize);

    cout << "Enter the generator bits (0 or 1) one by one:\n";
    for (int i = 0; i < generatorSize; i++) 
	{
        cin >> generator[i];
    }

    // Add zeros to the end of the data for the CRC division
    vector<int> encodedData(data);
    encodedData.insert(encodedData.end(), generatorSize - 1, 0);

    // Perform CRC division
    vector<int> remainder = performCRC(encodedData, generator);

    // Append the remainder to the encoded data
    encodedData.insert(encodedData.end(), remainder.begin(), remainder.end());

    cout << "Enter the received data bits (0 or 1) one by one:\n";
    for (int i = 0; i < encodedData.size(); i++) 
	{
        cin >> encodedData[i];
    }

    // Check if there is an error and correct it
    if (detectAndCorrectError(encodedData, generator)) 
	{
        cout << "Error detected and corrected. The corrected data is:\n";
        for (int i = 0; i < encodedData.size(); i++) 
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

