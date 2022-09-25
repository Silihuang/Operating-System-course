# include <iostream> // cout, endl
# include <string.h> // string
# include <vector> // vector
# include <cstdlib> // atoi, system
# include <iomanip> // setw, setprecision
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <sstream>
# include <math.h>
# include <queue>
# include <cmath>
# include <fstream>

using namespace std ;

class ProcessType {
public:
  int mProcessID = 0 ;
  int mCpuBurst = 0 ;
  int mArrivalTime = 0 ;
  int mPriority = 0 ;

  int mFCFSWTime = 0 ;  
  int mFCFSTurnTime = 0 ;
  int mNSJFWTime = 0 ;
  int mNSJFTurnTime = 0 ;
  int mPSJFWTime = 0 ;
  int mPSJFTurnTime = 0 ;
  int mRRWTime = 0 ;
  int mRRTurnTime = 0 ;
  int mPPWTime = 0 ;
  int mPPTurnTime = 0 ; 
  bool inQueue = false ;
  bool beUsed = false ; 
  int beUsedtime = 0 ; // �����Q�ϥΪ��ɶ� 
};

fstream file ; // Ū��
static int uTimeslice = 0 ; // �ɶ����q 
static vector <ProcessType> uAllProcess ; // �s�F�Ҧ�Process���A
// ------�̯S��------ 
static string uFCFSGrantt = "" ;
static string uNSJFGrantt = "" ; 
static string uPSJFGrantt = "" ; 
static string uRRGrantt = "" ; 
static string uPPGrantt = "" ; 
// ------�̯S��------

void StoreProcess() {
// �Nprocess��Ʀs��uAllProcess��
// type 1 : FCFS 
// type 2 : NSJF
// type 3 : PSJF
// type 4 : RR
// type 5 : PP
// type 6 : All
  string line = "" ;
  getline( file, line ) ; // �N���YŪ�h 
  while( getline( file, line ) ) {
	// �ĤT��}�l�C��̧Ǭ�
	// [ProcessID] [CPUBurst] [arrival time] [Priority]
    ProcessType store ;
    int word = 0 ;
    istringstream ss( line ) ;
    ss >> word ;
    store.mProcessID = word ;
    ss >> word ;
    store.mCpuBurst = word ;
    ss >> word ;
    store.mArrivalTime = word ;
    ss >> word ;
    store.mPriority = word ;
    uAllProcess.push_back( store ) ;
  } // while

  file.close() ;
  // �̷�ProcessID�Ѥp��j�Ƨ�
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    for( int j = i ; j < uAllProcess.size() ; j++ ) {
       if ( uAllProcess.at( i ).mProcessID > uAllProcess.at( j ).mProcessID ) {
       // �n�O�᭱���Ƥ���p
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	   } // if 
    } // for
  } // for

} // StoreProcess()

void WriteFile( int type, string filename ) {
// �g��
  // �̷�ProcessID�Ѥp��j�Ƨ�
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    for( int j = i ; j < uAllProcess.size() ; j++ ) {
       if ( uAllProcess.at( i ).mProcessID > uAllProcess.at( j ).mProcessID ) {
       // �n�O�᭱���Ƥ���p
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	   } // if 
    } // for
  } // for

  fstream file ;
  filename.erase( filename.begin(), filename.begin() + 5 ) ; // �N"input"���R���d�U�Ʀr 
  filename = "output" + filename ;
  file.open( filename.c_str(), ios::out ) ;
  switch( type ) {
    case 1 : // FCFS
      file << "==    FCFS==" << endl ;
	  file << "-" << uFCFSGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID      FCFS" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID 
		     << std::left << setw(8) << uAllProcess.at( i ).mFCFSWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID      FCFS" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mFCFSTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 2 : // NSJF
      file << "==    NSJF==" << endl ;
	  file << "-" << uNSJFGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID      NSJF" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mNSJFWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID      NSJF" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mNSJFTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 3 : // PSJF
      file << "==    PSJF==" << endl ;
	  file << "-" << uPSJFGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID      PSJF" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mPSJFWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID      PSJF" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) <<uAllProcess.at( i ).mPSJFTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 4 : // RR
      file << "==      RR==" << endl ;
	  file << "-" << uRRGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID        RR" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mRRWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID        RR" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mRRTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 5 : // PP
      file << "==      PP==" << endl ;
	  file << "-" << uPPGrantt << endl ;
	  file << "===========================================================" << endl ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID  Priority" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mPPWTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID  Priority" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mPPTurnTime << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    case 6 : // ����
      file << "==    FCFS==" << endl ;
	  file << "-" << uFCFSGrantt << endl ;
      file << "==      RR==" << endl ;
	  file << "-" << uRRGrantt << endl ;
      file << "==    PSJF==" << endl ;
	  file << "-" << uPSJFGrantt << endl ;
      file << "==Non-PSJF==" << endl ;
	  file << "-" << uNSJFGrantt << endl ;
      file << "== Priority==" << endl ;
	  file << "-" << uPPGrantt << endl ;
	  file << "===========================================================" << endl 
	       << "                                                                                " ;
	  file << endl << "Waiting Time" << endl ;
	  file << "ID      FCFS    RR      PSJF    NPSJF   Priority" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mFCFSWTime 
		     << std::left << setw(8) << uAllProcess.at( i ).mRRWTime << std::left << setw(8) << uAllProcess.at( i ).mPSJFWTime 
			 << std::left << setw(8) << uAllProcess.at( i ).mNSJFWTime << uAllProcess.at( i ).mPPWTime<< endl ;
	  } // for
	  file << "===========================================================" << endl ;
	  file << endl << "Turnaround Time" << endl ;
	  file << "ID      FCFS    RR      PSJF    NPSJF   Priority" << endl ;
	  file << "===========================================================" << endl ;
	  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
        file << std::left << setw(8) << uAllProcess.at( i ).mProcessID << std::left << setw(8) << uAllProcess.at( i ).mFCFSTurnTime 
		     << std::left << setw(8) << uAllProcess.at( i ).mRRTurnTime << std::left << setw(8) << uAllProcess.at( i ).mPSJFTurnTime 
			 << std::left << setw(8) << uAllProcess.at( i ).mNSJFTurnTime << uAllProcess.at( i ).mPPTurnTime  << endl ;
	  } // for
	  file << "===========================================================" << endl ;
    break ;
    default:
    break ;	
  } // switch 

  file.close() ;
} // WriteFile()

void FCFSMethod() {
// First Come First Served
// Non-preemptive
// ��������///������}�� 
   int CycleSum = 0 ; // �`�@�ݭn��h�֮ɶ�
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // �̷�ArrivalTime�Ѥp��j�Ƨ�
    for( int j = i + 1 ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime < uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // �P�ɩ�F�BPriority�p����e�� 
        if ( uAllProcess.at( i ).mPriority > uAllProcess.at( j ).mPriority )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if
    } // for
  } // for

  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) CycleSum = CycleSum + uAllProcess.at( i ).mCpuBurst ; 
  int count = 1 ; // Cycle�B�Ψӭp��Turnaround�BWaiting Time
  ProcessType RunProcess ;
  int NextArrivalProcess = 0 ; // �����U�@�ӻݭn��i�hQueue��Process��} 
  vector< ProcessType > Process = uAllProcess ; 
  vector< ProcessType > ReadQueue ; // �ǳƦ�C 
  while ( count <= CycleSum ) {
    // �N�w�g��F��Process��JQueue���A���]�t�w�g������Process 
    for( int i = 0 ; i < Process.size() ; i++ ) {
      if( Process.at( i ).mArrivalTime <= count && Process.at( i ).mCpuBurst != 0 && !Process.at( i ).inQueue ) {
        ReadQueue.push_back( Process.at( i ) ) ;
        Process.at( i ).inQueue = true ;
	  } // if
	} // for
    // for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).beUsedtime << " ";
	// cout << endl << "------------------------"  << endl ; 
    // �NQueue�Ƨ�
    if ( ReadQueue.size() > 0 ) {
      for ( int i = 0 ; i < ReadQueue.size() ; i++ ) {
        for ( int j = i + 1 ; j < ReadQueue.size() ; j++ ) { 
	      if ( ReadQueue.at( j ).mArrivalTime > ReadQueue.at( i ).mArrivalTime ) {
	          // Priority�ۦP�A�B��ӳ��ιL�γ��S�ιL�A�h���쪺������ 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
		  } // else if
          else if ( ReadQueue.at( j ).mArrivalTime == ReadQueue.at( i ).mArrivalTime 
                    && ReadQueue.at( j ).mProcessID > ReadQueue.at( i ).mProcessID ) {
            // Priority�ۦP�A�B��ӳ��ιL�γ��S�ιL�BArrivalTime�ۦP�AProcessId�p���ƫe�� 
		    swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
          } // else if
 	    } // for
	  } // for
       //for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).beUsedtime << " ";
	   //cout << endl << endl << endl << endl ; 
      // �]�w���b���檺Process�B�]�w�̯S��
      //cout << RunProcess.mProcessID << endl ;
      for( int i = 0 ; i < Process.size() ; i++ ) {
        if( Process.at( i ).mProcessID == ReadQueue.front().mProcessID ) {
          Process.at( i ).mCpuBurst = Process.at( i ).mCpuBurst - 1 ; // ����@��Cycle�ݭn��time-1
          if ( !ReadQueue.front().beUsed ) ReadQueue.front().beUsedtime = count ; // ����CPU�ϥιL���ɶ�
          ReadQueue.front().beUsed = true ; 
          ReadQueue.front().mCpuBurst = ReadQueue.front().mCpuBurst - 1 ;
          char id = '\0' ;
          if ( Process.at( i ).mProcessID > 9 ) { // 10�H�W���ƥέ^��r���
            id = Process.at( i ).mProcessID + '7' ;
	      } // if
          else {
            id = Process.at( i ).mProcessID + '0' ;
	      } // else 
          uFCFSGrantt = uFCFSGrantt + id ; // ��J�̯S��  
	    } // if
	  } // for

      // �p��Waiting time  
      // ReadQueue�̰��F�Ĥ@��Process�H�~�A���bWaiting�B�p�GArrival�]�N�|�bReadyQueue�� 
      for ( int i = 1  ; i < ReadQueue.size() ; i++ ) {
        for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
          if ( uAllProcess.at( j ).mProcessID == ReadQueue.at( i ).mProcessID ) {
            // �����Process�������uAllProcess 
            uAllProcess.at( j ).mFCFSWTime = uAllProcess.at( j ).mFCFSWTime + 1 ;
          } // if 
        } // for 
      } // for
      // ������Process�qQueue����
  	  RunProcess = ReadQueue.front()  ;
      if ( RunProcess.mCpuBurst == 0 ) {
        ReadQueue.erase( ReadQueue.begin() ) ;
  	  } // if
	} // if
	else {
	  // �YCPU�����m�A�@�ˬ��� 
      uFCFSGrantt = uFCFSGrantt + "-" ;	
      CycleSum++ ;
	} // else 

    count++ ;
  } // while 

  // �p��Turnaround time  
  // Turnaroundtime = waiting time + burst time
  for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
    uAllProcess.at( j ).mPPTurnTime = uAllProcess.at( j ).mPPWTime + uAllProcess.at( j ).mCpuBurst ;
  } // for 

  // cout << uFCFSGrantt << endl ;
  // for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mFCFSWTime << endl ;; 
} // FCFS()

void NSJFMethod() {
// Shortest Job First
// Non-preemptive
// �C������Process�e�A�N�bReady Queue��Process�̾�burst�Ѥp��j
// burst�ۦP�h�̾�ArrivalTime�Ѥp��j 

  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // �̷�ArrivalTime�Ѥp��j�Ƨ�
    for( int j = i ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime > uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // �P�ɩ�F�Bburst�p����e�� 
        if ( uAllProcess.at( i ).mCpuBurst > uAllProcess.at( j ).mCpuBurst )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if  
    } // for
  } // for

  int count = 1 ; // Cycle�B�Ψӭp��Turnaround�BWaiting Time 
  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) {
  // ��BurstTime�̤p���}�l�]�B��J�̯S��
    if ( count >= uAllProcess.at( i ).mArrivalTime ) {
      // uAllProcess��F
      for ( int k = i ; k < uAllProcess.size() ; k++ ) {
        // �ݭn�P�_�w��F�������ǡA�h���Ƨ�
        for ( int j = k ; j < uAllProcess.size() ; j++ ) {
          if ( count >= uAllProcess.at( j ).mArrivalTime && uAllProcess.at( j ).mCpuBurst < uAllProcess.at( k ).mCpuBurst ) {
            // �w��F��uAllProcess�A�p�GCpuburst���p�h������ 
            swap( uAllProcess.at( j ), uAllProcess.at( k ) ) ; 
	      } // if
	      else if ( count >= uAllProcess.at( j ).mArrivalTime && uAllProcess.at( j ).mCpuBurst == uAllProcess.at( k ).mCpuBurst ) {
	        // Cpuburst�ۦP�A�h���쪺������ 
            if ( uAllProcess.at( j ).mArrivalTime < uAllProcess.at( k ).mArrivalTime ) swap( uAllProcess.at( j ), uAllProcess.at( k ) ) ; 
		  } // else if  
        } // for
      } // for     	 	
      // �w�g��F 
      uAllProcess.at( i ).mNSJFWTime = count - uAllProcess.at( i ).mArrivalTime ; // Waiting���ɶ����ƶ��ɶ� 
  	  for ( int burst = uAllProcess.at( i ).mCpuBurst ; burst > 0 ; burst--, count++ ) {
        // ����uAllProcess�B���Burst time 
        char id = '\0' ;
        if ( uAllProcess.at( i ).mProcessID > 9 ) { // 10�H�W���ƥέ^��r���
          id = uAllProcess.at( i ).mProcessID + '7' ;
	    } // if
	    else {
          id = uAllProcess.at( i ).mProcessID + '0' ;
	    } // else 
        uNSJFGrantt = uNSJFGrantt + id ; // ��J�̯S�� 
      } // for

      uAllProcess.at( i ).mNSJFTurnTime = uAllProcess.at( i ).mNSJFWTime + uAllProcess.at( i ).mCpuBurst  ; 
      // Turnaround time = waiting time + bursttime

    } // if 
    else {
      // �S��uAllProcess��F�B�֭pCycle 
      while( count < uAllProcess.at( i ).mArrivalTime ) {
      	uNSJFGrantt = uNSJFGrantt + "-" ;
        count = count + 1 ; 
      } // while

      i = i - 1 ; // ������uAllProcess�S���Count�֥[��B�U���j��|�ܥt�@�ӡB�G-1�ܦ^��Ӫ� 
	} // else
 
  } // for

  // cout << uNSJFGrantt << endl ;
  // for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mNSJFWTime << endl ;; 
} // NSJFMethod()

void PSJFMethod() {
// Preemptive Shortest Job First( SRTF )
// preemptive
// �C���s��Process�i�ӡA���burst�j�p�C 
// �Ѿl��CPU Burst�ۦP, ���S���ιLCPU�����ϥ�, �L�k���O�ɫh��arrival time�p�����B�z
// �Y�ѾlCPU Burst�ۦP�Barrival time�ۦP, �h��ProcessID�Ѥp�ܤj�̧ǳB�z�C  
// ���O��CPU��process��CPU Burst����ready��C�̲Ĥ@��process��CPU Burst�A�B�Ƨ���C�̲Ĥ@��process�|���Q�ϥΨä��|�o�ͷm��
  int CycleSum = 0 ; // �`�@�ݭn��h�֮ɶ�
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // �̷�ArrivalTime�Ѥp��j�Ƨ�
    for( int j = i + 1 ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime < uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // �P�ɩ�F�BPriority�p����e�� 
        if ( uAllProcess.at( i ).mPriority > uAllProcess.at( j ).mPriority )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if
    } // for
  } // for

  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) CycleSum = CycleSum + uAllProcess.at( i ).mCpuBurst ; 
  int count = 1 ; // Cycle�B�Ψӭp��Turnaround�BWaiting Time
  ProcessType RunProcess ;
  int NextArrivalProcess = 0 ; // �����U�@�ӻݭn��i�hQueue��Process��} 
  vector< ProcessType > Process = uAllProcess ; 
  vector< ProcessType > ReadQueue ; // �ǳƦ�C 
  while ( count <= CycleSum ) {

    // �N�w�g��F��Process��JQueue���A���]�t�w�g������Process 
    for( int i = 0 ; i < Process.size() ; i++ ) {
      if( Process.at( i ).mArrivalTime <= count && Process.at( i ).mCpuBurst != 0 && !Process.at( i ).inQueue ) {
        ReadQueue.push_back( Process.at( i ) ) ;
        Process.at( i ).inQueue = true ;
	  } // if
	} // for

    //for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).mCpuBurst << " ";
    //cout << endl << "------------------------"  << endl ; 
    // �NQueue�Ƨ�
    for ( int i = 0 ; i < ReadQueue.size() ; i++ ) {
      for ( int j = i + 1 ; j < ReadQueue.size() ; j++ ) {
       // if ( ReadQueue.at( j ).mProcessID == 4 ) cout << ReadQueue.at( i ).beUsedtime << endl ; 
        if ( ReadQueue.at( j ).mCpuBurst == ReadQueue.at( i ).mCpuBurst 
			 && i == 0 && ReadQueue.at( i ).mProcessID == RunProcess.mProcessID
			 && !ReadQueue.at( j ).beUsed ) { // �S�� 
		  // �P�_CPU�̪�Process�O���O�٬O�W����Proces 
          // ��CPU��process��burst����ready��C�̲Ĥ@��process��burst
		  // �Ƨ���C�̲Ĥ@��burst�|���Q�ϥΨä��|�o�ͷm��
	    } // if
        else if ( ReadQueue.at( j ).mCpuBurst < ReadQueue.at( i ).mCpuBurst ) {
          // �w��F��Process�A�p�Gburst���p�h������ 
          swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	    } // else if
        else if ( ReadQueue.at( j ).mCpuBurst == ReadQueue.at( i ).mCpuBurst 
                  && ( !ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed ) ) {
          // �@�Ӧ��ιL�@�ӨS�ιL�Aburst�ۦP, ���S���ιLCPU�����ϥ�
          swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	    } // else if
	    else if ( ReadQueue.at( j ).mCpuBurst == ReadQueue.at( i ).mCpuBurst 
                  && ( !ReadQueue.at( j ).beUsed && !ReadQueue.at( i ).beUsed 
				  || ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed )   
                  && ReadQueue.at( j ).mArrivalTime < ReadQueue.at( i ).mArrivalTime ) {
	        // burst�ۦP�A�B��ӳ��S�ιL���γ��ιL�A�h���쪺������ 
          swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
		} // else if
        else if ( ReadQueue.at( j ).mCpuBurst == ReadQueue.at( i ).mCpuBurst 
                  && ( !ReadQueue.at( j ).beUsed && !ReadQueue.at( i ).beUsed 
				  || ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed )  
		          && ReadQueue.at( j ).mArrivalTime == ReadQueue.at( i ).mArrivalTime 
                  && ReadQueue.at( j ).mProcessID < ReadQueue.at( i ).mProcessID ) {
          // burst�ۦP�A�B��ӳ��S�ιL���γ��ιL�BArrivalTime�ۦP�AProcessId�p���ƫe�� 
		  swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
        } // else if
 	  } // for
	} // for
 
     //for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).mCpuBurst << " ";
	 //cout << endl << endl << endl << endl ; 
    // �]�w���b���檺Process�B�]�w�̯S��
    if ( ReadQueue.size() > 0 ) {
      // �T�OCPU��Process�ݭn���� 
      for( int i = 0 ; i < Process.size() ; i++ ) {
        if( Process.at( i ).mProcessID == ReadQueue.front().mProcessID ) {
          Process.at( i ).mCpuBurst = Process.at( i ).mCpuBurst - 1 ; // ����@��Cycle�ݭn��time-1
          if ( !ReadQueue.front().beUsed ) ReadQueue.front().beUsedtime = count ; // ����CPU�ϥιL���ɶ�
          ReadQueue.front().beUsed = true ; 
          ReadQueue.front().mCpuBurst = ReadQueue.front().mCpuBurst - 1 ;
          char id = '\0' ;
          if ( Process.at( i ).mProcessID > 9 ) { // 10�H�W���ƥέ^��r���
            id = Process.at( i ).mProcessID + '7' ;
	      } // if
    	  else {
            id = Process.at( i ).mProcessID + '0' ;
	      } // else 
          uPSJFGrantt = uPSJFGrantt + id ; // ��J�̯S��  
	    } // if
  	  } // for
      // �p��Waiting time  
      // ReadQueue�̰��F�Ĥ@��Process�H�~�A���bWaiting�B�p�GArrival�]�N�|�bReadyQueue�� 
      for ( int i = 1 ; i < ReadQueue.size() ; i++ ) {
        for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
          if ( uAllProcess.at( j ).mProcessID == ReadQueue.at( i ).mProcessID ) {
            // �����Process�������uAllProcess 
            uAllProcess.at( j ).mPSJFWTime = uAllProcess.at( j ).mPSJFWTime + 1 ;
          } // if 
        } // for 
      } // for
      // ������Process�qQueue����
  	  RunProcess = ReadQueue.front()  ;
      if ( RunProcess.mCpuBurst == 0 ) {
        ReadQueue.erase( ReadQueue.begin() ) ;
	  } // if

    } // if
    else {
      // �p�GCPU�Ŷ��A�@�ˬ����̯S�� 
      uPSJFGrantt = uPSJFGrantt + "-" ;
 	  CycleSum++ ;
	} // else

    count++ ;
  } // while 

  // �p��Turnaround time  
  // Turnaroundtime = waiting time + burst time
  for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
    uAllProcess.at( j ).mPSJFTurnTime = uAllProcess.at( j ).mPSJFWTime + uAllProcess.at( j ).mCpuBurst ;
  } // for 

  // cout << uPSJFGrantt << endl ;
  //for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mPPWTime << endl ;; 
} // PJSFMethod()

void RRMethod() {
// RoundRobin
// preemptive
// �C��@�ӷs��time slice�A�qqueue�̫e�����XProcess���� 
// Queue�L�ƧǱ��p
// �C�s���@��Time slice�~�NProcess����᭱ 
  int CycleSum = 0 ; // �`�@�ݭn��h�֮ɶ� 
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // �̷�ArrivalTime�Ѥp��j�Ƨ�
    for( int j = i ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime > uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // �P�ɩ�F�Bburst�p����e�� 
        if ( uAllProcess.at( i ).mProcessID > uAllProcess.at( j ).mProcessID )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if  
    } // for
  } // for

  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) CycleSum = CycleSum + uAllProcess.at( i ).mCpuBurst ; 
  int count = 1 ; // Cycle�B�Ψӭp��Turnaround�BWaiting Time
  int NextArrivalProcess = 0 ; // �����U�@�ӻݭn��i�hQueue��Process��} 
  int cpuslice = 1 ; // �p��s��Process�bCPU���檺�ɶ��A�p�GProcess������timeout�h�k�s 
  ProcessType RunProcess ;
  vector< ProcessType > Process = uAllProcess ; 
  vector< ProcessType > ReadyQueue ; // �ǳƦ�C 
  while ( count <= CycleSum ) {
    // �N�w�g��F��Process��JQueue���A���]�t�w�g������Process 
    for( int k = NextArrivalProcess ; k < Process.size() ; k++ ) {
      if( Process.at( k ).mArrivalTime <= count && Process.at( k ).mCpuBurst != 0 && !Process.at( k ).inQueue ) {
        ReadyQueue.push_back( Process.at( k ) ) ;
        Process.at( k ).inQueue = true ; 
        NextArrivalProcess = k + 1 ;
	  } // if
	} // for

    // �p�GProcess��timeslice��F�o�P�ɦ��s���i�ӡA�ݭn�����s���iQUEUE 
    if ( RunProcess.mCpuBurst != 0 && cpuslice == 1 && count != 1 ) ReadyQueue.push_back( RunProcess ) ; 

	if ( ReadyQueue.size() > 0 ) {
      // �]�w���b���檺Process�B�]�w�̯S�� 
      for( int i = 0 ; i < Process.size() ; i++ ) {
        if( Process.at( i ).mProcessID == ReadyQueue.front().mProcessID ) {
          Process.at( i ).mCpuBurst = Process.at( i ).mCpuBurst - 1 ; // ����@��Cycle�ݭn��time-1 
          ReadyQueue.front().mCpuBurst = ReadyQueue.front().mCpuBurst - 1 ;
          char id = '\0' ;
          if ( Process.at( i ).mProcessID > 9 ) { // 10�H�W���ƥέ^��r���
            id = Process.at( i ).mProcessID + '7' ;
	      } // if
      	  else {
            id = Process.at( i ).mProcessID + '0' ;
	      } // else 
          uRRGrantt = uRRGrantt + id ; // ��J�̯S��  
	    } // if
	  } // for
    // ���檺Process�p�G��FTimeslice�qQueue�̫e�����̫᭱
	// �����h�qReadyQueue�̫e������ 
      RunProcess = ReadyQueue.front() ;
      if ( RunProcess.mCpuBurst == 0 || cpuslice == uTimeslice ) {
        ReadyQueue.erase( ReadyQueue.begin() ) ;
        cpuslice = 0 ; // �ﱵ�s��Process 
  	  } // if 
      // �p��Waiting time  
      // ReadQueue�̰��F�Ĥ@��Process�H�~�A���bWaiting�B�p�GArrival�]�N�|�bReadyQueue�� 
      for ( int i = 0 ; i < ReadyQueue.size() ; i++ ) {
        for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
          if ( uAllProcess.at( j ).mProcessID == ReadyQueue.at( i ).mProcessID && ReadyQueue.at( i ).mProcessID != RunProcess.mProcessID ) {
            // �����Process�������uAllProcess 
            uAllProcess.at( j ).mRRWTime = uAllProcess.at( j ).mRRWTime + 1 ;
          } // if 
        } // for 
      } // for

	  cpuslice = cpuslice + 1 ; 
	} // if 
	else {
	  // �YCPU���m�B�@�ˬ��� 
	  uRRGrantt = uRRGrantt + "-" ;
      CycleSum++ ;  
	} // else 
	
	count = count + 1 ;
  } // while 
  // �p��Turnaround time  
  // Turnaroundtime = waiting time + burst time
  for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
    uAllProcess.at( j ).mRRTurnTime = uAllProcess.at( j ).mRRWTime + uAllProcess.at( j ).mCpuBurst ;
  } // for 

  // cout << uRRGrantt << endl ;
  // for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mRRWTime << endl ;; 
} // RRMethod()

void PPMethod() {
// Priority
// preemptive
// �C���s��Process�i�ӡA���Priority�j�p�C 
// �Ѿl��Priority�ۦP, ���S���ιLCPU�����ϥ�, �L�k���O�ɫh��arrival time�p�����B�z
// �Y�ѾlPriority�ۦP�Barrival time�ۦP, �h��ProcessID�Ѥp�ܤj�̧ǳB�z�C  
// ���O��CPU��process��Priority����ready��C�̲Ĥ@��process��Priority�A�B�Ƨ���C�̲Ĥ@��process�|���Q�ϥΨä��|�o�ͷm��
  int CycleSum = 0 ; // �`�@�ݭn��h�֮ɶ�
  for( int i = 0 ; i < uAllProcess.size() ; i++ ) {
    // �̷�ArrivalTime�Ѥp��j�Ƨ�
    for( int j = i + 1 ; j < uAllProcess.size() ; j++ ) {
      if ( uAllProcess.at( i ).mArrivalTime < uAllProcess.at( j ).mArrivalTime ) {
         swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // if
      else if ( uAllProcess.at( i ).mArrivalTime == uAllProcess.at( j ).mArrivalTime ) {
       // �P�ɩ�F�BPriority�p����e�� 
        if ( uAllProcess.at( i ).mPriority > uAllProcess.at( j ).mPriority )
          swap( uAllProcess.at( i ), uAllProcess.at( j ) ) ; 
	  } // else if
    } // for
  } // for

  for ( int i = 0 ; i < uAllProcess.size() ; i++ ) CycleSum = CycleSum + uAllProcess.at( i ).mCpuBurst ; 
  int count = 1 ; // Cycle�B�Ψӭp��Turnaround�BWaiting Time
  ProcessType RunProcess ;
  int NextArrivalProcess = 0 ; // �����U�@�ӻݭn��i�hQueue��Process��} 
  vector< ProcessType > Process = uAllProcess ; 
  vector< ProcessType > ReadQueue ; // �ǳƦ�C 
  while ( count <= CycleSum ) {

    // �N�w�g��F��Process��JQueue���A���]�t�w�g������Process 
    for( int i = 0 ; i < Process.size() ; i++ ) {
      if( Process.at( i ).mArrivalTime <= count && Process.at( i ).mCpuBurst != 0 && !Process.at( i ).inQueue ) {
        ReadQueue.push_back( Process.at( i ) ) ;
        Process.at( i ).inQueue = true ;
	  } // if
	} // for

    // for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).beUsedtime << " ";
	// cout << endl << "------------------------"  << endl ; 
    // �NQueue�Ƨ�
    if ( ReadQueue.size() > 0 ) {
      for ( int i = 0 ; i < ReadQueue.size() ; i++ ) {
        for ( int j = i + 1 ; j < ReadQueue.size() ; j++ ) { 
        // if ( ReadQueue.at( j ).mProcessID == 4 ) cout << ReadQueue.at( i ).beUsedtime << endl ; 
          /*if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
		        && i == 0 && ReadQueue.at( i ).mProcessID == RunProcess.mProcessID ) {
		    // �P�_CPU�̪�Process�O���O�٬O�W����Proces 
            // ��CPU��process��Priority����ready��C�̲Ĥ@��process��Priority
		    // �Ƨ���C�̲Ĥ@��process�|���Q�ϥΨä��|�o�ͷm��
	      } // if
          else if ( ReadQueue.at( j ).mPriority < ReadQueue.at( i ).mPriority ) {
            // �w��F��Process�A�p�GPriority���p�h������ 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	      } // else if
          else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
                    && ( !ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed ) 
				    && ReadQueue.at( i ).beUsedtime > ReadQueue.at( j ).beUsedtime ) {
            // �@�Ӧ��ιL�@�ӨS�ιL�APriority�ۦP, ���S���ιLCPU�����ϥ�
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	      } // else if
	      else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
	                && ( !ReadQueue.at( j ).beUsed && !ReadQueue.at( i ).beUsed || ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed ) 
                    && ReadQueue.at( j ).mArrivalTime < ReadQueue.at( i ).mArrivalTime ) {
	          // Priority�ۦP�A�B��ӳ��ιL�γ��S�ιL�A�h���쪺������ 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
		  } // else if
          else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
	                && ( !ReadQueue.at( j ).beUsed && !ReadQueue.at( i ).beUsed || ReadQueue.at( j ).beUsed && ReadQueue.at( i ).beUsed )  
		            && ReadQueue.at( j ).mArrivalTime == ReadQueue.at( i ).mArrivalTime 
                    && ReadQueue.at( j ).mProcessID < ReadQueue.at( i ).mProcessID ) {
            // Priority�ۦP�A�B��ӳ��ιL�γ��S�ιL�BArrivalTime�ۦP�AProcessId�p���ƫe�� 
		    swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
          } // else if*/
		  if ( i == 0 && ReadQueue.at( i ).mProcessID == RunProcess.mProcessID ) {
		    // �ק��D���m�� 
	      } // if
          else if ( ReadQueue.at( j ).mPriority < ReadQueue.at( i ).mPriority ) {
            // �w��F��Process�A�p�GPriority���p�h������ 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ; 
	      } // if
	      else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority 
                    && ReadQueue.at( j ).mArrivalTime < ReadQueue.at( i ).mArrivalTime ) {
	          // Priority�ۦP�A�B��ӳ��ιL�γ��S�ιL�A�h���쪺������ 
            swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
		  } // else if
          else if ( ReadQueue.at( j ).mPriority == ReadQueue.at( i ).mPriority  
		            && ReadQueue.at( j ).mArrivalTime == ReadQueue.at( i ).mArrivalTime 
                    && ReadQueue.at( j ).mProcessID > ReadQueue.at( i ).mProcessID ) {
            // Priority�ۦP�A�B��ӳ��ιL�γ��S�ιL�BArrivalTime�ۦP�AProcessId�p���ƫe�� 
		    swap( ReadQueue.at( j ), ReadQueue.at( i ) ) ;
          } // else if
 	    } // for
	  } // for
       // for ( int i = 0 ; i < ReadQueue.size() ; i++ ) cout << ReadQueue.at(i).mProcessID << "-" <<ReadQueue.at(i).beUsedtime << " ";
	   // cout << endl << endl << endl << endl ; 
      // �]�w���b���檺Process�B�]�w�̯S��
      for( int i = 0 ; i < Process.size() ; i++ ) {
        if( Process.at( i ).mProcessID == ReadQueue.front().mProcessID ) {
          Process.at( i ).mCpuBurst = Process.at( i ).mCpuBurst - 1 ; // ����@��Cycle�ݭn��time-1
          if ( !ReadQueue.front().beUsed ) ReadQueue.front().beUsedtime = count ; // ����CPU�ϥιL���ɶ�
          ReadQueue.front().beUsed = true ; 
          ReadQueue.front().mCpuBurst = ReadQueue.front().mCpuBurst - 1 ;
          char id = '\0' ;
          if ( Process.at( i ).mProcessID > 9 ) { // 10�H�W���ƥέ^��r���
            id = Process.at( i ).mProcessID + '7' ;
	      } // if
          else {
            id = Process.at( i ).mProcessID + '0' ;
	      } // else 
          uPPGrantt = uPPGrantt + id ; // ��J�̯S��  
	    } // if
	  } // for

      // �p��Waiting time  
      // ReadQueue�̰��F�Ĥ@��Process�H�~�A���bWaiting�B�p�GArrival�]�N�|�bReadyQueue�� 
      for ( int i = 1 ; i < ReadQueue.size() ; i++ ) {
        for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
          if ( uAllProcess.at( j ).mProcessID == ReadQueue.at( i ).mProcessID ) {
            // �����Process�������uAllProcess 
            uAllProcess.at( j ).mPPWTime = uAllProcess.at( j ).mPPWTime + 1 ;
          } // if 
        } // for 
      } // for
      // ������Process�qQueue����
  	  RunProcess = ReadQueue.front()  ;
      if ( RunProcess.mCpuBurst == 0 ) {
        ReadQueue.erase( ReadQueue.begin() ) ;
  	  } // if
	} // if
	else {
	  // �YCPU�����m�A�@�ˬ��� 
      uPPGrantt = uPPGrantt + "-" ;	
      CycleSum++ ;
	} // else 

    count++ ;
  } // while 

  // �p��Turnaround time  
  // Turnaroundtime = waiting time + burst time
  for( int j = 0 ; j < uAllProcess.size() ; j++ ) {
    uAllProcess.at( j ).mPPTurnTime = uAllProcess.at( j ).mPPWTime + uAllProcess.at( j ).mCpuBurst ;
  } // for 

  // cout << uPPGrantt << endl ;
  //for ( int i = 0 ; i < uAllProcess.size() ; i++ ) cout << uAllProcess.at( i ).mPPWTime << endl ;; 
} // PPMethod()

int main(int argc, char** argv) {

  string filename = "" ;
  cin >> filename ; // Ū���ɮצW��
  filename = filename + ".txt" ;
  file.open( filename.c_str(), ios::in ) ;
  while( !file ) { // ���b 
    cin >> filename ; // Ū���ɮצW��
    filename = filename + ".txt" ;
    file.open( filename.c_str(), ios::in ) ;
    cout << "Wrong FileName" << endl ;
  } // while 

  // �Ĥ@��Ĥ@��integer��method,�d��1~6
  string line = "" ;
  int method = 0 ;
  getline( file, line ) ;
  istringstream ss( line ) ;
  ss >> method ;   // stirng�নInt���O
  // �Ĥ@��ĤG��integer��time slice,�d�򤣩w
  ss >> uTimeslice ;  // stirng�নInt���O

  StoreProcess() ; // �Nprocess��Ʀs��uAllProcess�� 

  switch( method ) {

    case 1 : // FCFS
      FCFSMethod() ; 
      WriteFile( 1, filename ) ;
    break ;
    case 2 : // NSJF
      NSJFMethod() ;
      WriteFile( 2, filename ) ;
    break ;
    case 3 : // PSJF
      PSJFMethod() ;
      WriteFile( 3, filename ) ;
    break ;
    case 4 : // RR
      RRMethod() ;
      WriteFile( 4, filename ) ;
    break ;
    case 5 : // PP
      PPMethod() ;
      WriteFile( 5, filename ) ;
    break ;
    case 6 : // ����
      FCFSMethod() ; 
      NSJFMethod() ;
      PSJFMethod() ;
      RRMethod() ;
      PPMethod() ;
      WriteFile( 6, filename ) ;
    break ;
    default:
      cout << "Wrong Method" ;
    break ;
  } // switch

  return 0;
} // main 


