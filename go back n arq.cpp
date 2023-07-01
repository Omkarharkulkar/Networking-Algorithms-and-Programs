#include <iostream>
#include <vector>

using namespace std;

// Function to implement sliding window mechanism using Go Back N ARQ
void slidingWindow(vector<int> frames, int windowSize) 
{
    int n = frames.size();
    int sent = 0, ack = 0;

    while (sent < n) 
	{
        // Send frames within the window size
        for (int i = sent; i < min(sent + windowSize, n); i++) 
		{
            cout << "Sending frame " << frames[i] << endl;
        }

        // Wait for acknowledgement
        for (int i = ack; i < min(ack + windowSize, n); i++) 
		{
            int response;
            cout << "Enter acknowledgement for frame " << frames[i] << ": ";
            cin >> response;

            // If acknowledgement received, move the window
            if (response == 1) 
			{
                ack++;
            }
            // If acknowledgement not received, resend the frames
            else 
			{
                sent = ack;
                break;
            }
        }
    }
}

int main() 
{
    int n, windowSize;
    vector<int> frames;

    // Get input from user
    cout << "Enter the number of frames: ";
    cin >> n;

    cout << "Enter the frames: ";
    for (int i = 0; i < n; i++) 
	{
        int frame;
        cin >> frame;
        frames.push_back(frame);
    }

    cout << "Enter the window size: ";
    cin >> windowSize;

    // Call the sliding window function
    slidingWindow(frames, windowSize);

    return 0;
}
