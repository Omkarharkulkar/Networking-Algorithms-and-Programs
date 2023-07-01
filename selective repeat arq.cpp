#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to implement sliding window mechanism using selective repeat ARQ
void slidingWindowSelectiveRepeatARQ(vector<int> frames, int windowSize) 
{
    int n = frames.size();
    int base = 0, nextSeqNum = 0;
    vector<int> acks(n, -1);

    // Loop through the frames
    while (base < n) 
	{
        // Send frames within the window
        for (int i = base; i < min(base + windowSize, n); i++) 
		{
            cout << "Sending frame " << frames[i] << endl;
        }

        // Receive acknowledgements
        for (int i = base; i < min(base + windowSize, n); i++) 
		{
            if (acks[i] == -1) 
			{
                cout << "Waiting for acknowledgement for frame " << frames[i] << endl;
            }
            else 
			{
                cout << "Received acknowledgement for frame " << frames[i] << endl;
            }
        }

        // Check for timed-out frames
        for (int i = base; i < min(base + windowSize, n); i++) 
		{
            if (acks[i] == -1) 
			{
                cout << "Frame " << frames[i] << " timed out. Resending..." << endl;
            }
        }

        // Update base and nextSeqNum
        while (base < n && acks[base] != -1) 
		{
            base++;
        }
        nextSeqNum = base + windowSize;

        // Get user input to simulate acknowledgement
        for (int i = base; i < min(base + windowSize, n); i++) 
		{
            if (acks[i] == -1) 
			{
                cout << "Did frame " << frames[i] << " get acknowledged? (1 for yes, 0 for no): ";
                cin >> acks[i];
            }
        }
    }
}

int main() 
{
    // Get user input
    int n, windowSize;
    cout << "Enter number of frames: ";
    cin >> n;
    cout << "Enter window size: ";
    cin >> windowSize;
    vector<int> frames(n);
    cout << "Enter frame values: ";
    for (int i = 0; i < n; i++) 
	{
        cin >> frames[i];
    }

    // Call slidingWindowSelectiveRepeatARQ function
    slidingWindowSelectiveRepeatARQ(frames, windowSize);

    return 0;
}
