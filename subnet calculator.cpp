#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Function to calculate the number of host bits
int calculateHostBits(int subnetMask) {
    int hostBits = 32;
    while ((subnetMask & 1) == 0) {
        subnetMask >>= 1;
        hostBits--;
    }
    return hostBits;
}

// Function to calculate the number of hosts in a subnet
int calculateNumHosts(int hostBits) {
    return (1 << hostBits) - 2;
}

// Function to calculate the subnet mask from CIDR notation
int calculateSubnetMask(int cidr) {
    int subnetMask = 0xFFFFFFFF;
    subnetMask <<= (32 - cidr);
    return subnetMask;
}

// Function to convert an IP address to binary string format
string ipToBinaryString(const string& ipAddress) {
    stringstream ss(ipAddress);
    string binaryString = "";
    string segment;
    while (getline(ss, segment, '.')) {
        int value = atoi(segment.c_str());
        string binarySegment = "";
        for (int i = 7; i >= 0; i--) {
            binarySegment += ((value >> i) & 1) ? "1" : "0";
        }
        binaryString += binarySegment;
    }
    return binaryString;
}

// Function to calculate the network address given an IP address and subnet mask
string calculateNetworkAddress(const string& ipAddress, int subnetMask) {
    string ipBinary = ipToBinaryString(ipAddress);
    string networkBinary = "";
    for (int i = 0; i < 32; i++) {
        networkBinary += (ipBinary[i] == '1' && (subnetMask & (1 << (31 - i)))) ? "1" : "0";
    }
    string networkAddress = "";
    for (int i = 0; i < 4; i++) {
        int segment = 0;
        for (int j = 0; j < 8; j++) {
            segment = (segment << 1) + (networkBinary[i * 8 + j] - '0');
        }
        networkAddress += to_string(segment);
        if (i < 3)
            networkAddress += ".";
    }
    return networkAddress;
}

int main() {
    string ipAddress;
    int cidr;

    cout << "Enter the IP address: ";
    cin >> ipAddress;
    cout << "Enter the CIDR notation (e.g., 24 for /24): ";
    cin >> cidr;

    // Calculate the subnet mask and host bits
    int subnetMask = calculateSubnetMask(cidr);
    int hostBits = calculateHostBits(subnetMask);

    // Calculate the number of hosts in the subnet
    int numHosts = calculateNumHosts(hostBits);

    // Calculate the network address
    string networkAddress = calculateNetworkAddress(ipAddress, subnetMask);

    cout << "Network Address: " << networkAddress << endl;
    cout << "Subnet Mask: " << subnetMask << endl;
    cout << "Host Bits: " << hostBits << endl;
    cout << "Number of Hosts: " << numHosts << endl;

    return 0;
}

