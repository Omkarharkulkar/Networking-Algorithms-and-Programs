#include <iostream>
#include <vector>

using namespace std;

void sliding_window(vector<int> data, int window_size) {
    /*
    This function implements sliding window mechanism using stop and wait ARQ.
    
    Parameters:
    data (vector<int>): The data to be transmitted
    window_size (int): The size of the sliding window
    
    Returns:
    None
    */
    int n = data.size();
    int i = 0, j = 0;
    while (i < n) 
	{
        // Send the next window
        for (int k = i; k < min(i + window_size, n); k++) 
		{
            cout << "Sending packet " << data[k] << endl;
        }
        
        // Wait for acknowledgement
        for (int k = i; k < min(i + window_size, n); k++) 
		{
            cout << "Waiting for acknowledgement for packet " << data[k] << endl;
        }
        
        // Move the window
        i += window_size;
    }
}

int main() 
{
    // Get input from user
    int n, window_size;
    cout << "Enter the number of packets: ";
    cin >> n;
    cout << "Enter the window size: ";
    cin >> window_size;
    vector<int> data(n);
    cout << "Enter the packet data: ";
    
    for (int i = 0; i < n; i++) 
	{
        cin >> data[i];
    }
    
    // Call the sliding window function
    sliding_window(data, window_size);
    
    return 0;
}
