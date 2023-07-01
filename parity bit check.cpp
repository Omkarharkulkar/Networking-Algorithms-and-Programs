#include <iostream>
#include <vector>

using namespace std;

// Function to calculate the parity bit
int calculateParityBit(const vector<int>& data) 
{
    int count = 0;
    for (int i = 0; i < data.size(); i++) 
	{
        if (data[i])
            count++;
    }
    return count % 2; // Return 1 if count is odd, 0 if count is even
}

// Function to correct the single bit error
void correctError(vector<int>& data, int errorIndex) 
{
    data[errorIndex] = (data[errorIndex] + 1) % 2; // Flip the bit at the error index
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

    // Calculate the parity bit
    int parityBit = calculateParityBit(data);

    cout << "Enter the received data bits (0 or 1) one by one:\n";
    for (int i = 0; i < dataLength; i++) 
	{
        cin >> data[i];
    }

    // Calculate the received parity bit
    int receivedParityBit = calculateParityBit(data);

    // Check if there is a single bit error
    if (parityBit != receivedParityBit) 
	{
        cout << "Error detected in the received data.\n";

        // Find the error bit index
        int errorIndex = 0;
        for (int i = 0; i < dataLength; i++) 
		{
            if (data[i] != parityBit) 
			{
                errorIndex = i;
                break;
            }
        }

        // Correct the error
        correctError(data, errorIndex);

        cout << "Error corrected. The corrected data is:\n";
        for (int i = 0; i < dataLength; i++) 
		{
            cout << data[i] << " ";
        }
        cout << endl;
    } 
	else 
	{
        cout << "No error detected in the received data.\n";
    }

    return 0;
}

