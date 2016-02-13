#pragma once

#include "Runtime/Core/Public/Containers/Array.h"
#include "PlatformClientMessage.generated.h"

USTRUCT(BlueprintType, Category = "GamePlatformService_Message")
struct FPlatformMessageBlock
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, Category = "GamePlatformService_Message")
	FString messageData;
	int LoadMessageBlock(TArray<uint8> data, uint32 idx) {
		
		uint32 len = data[idx];
		messageData = "";
 		for (uint32 x = 0; x < len; x++) {
			int readIdx = x + idx + 1;
			messageData = messageData + data[readIdx];
		}
		return len + 1;
	};
	TArray<uint8> WriteMessageBlockData(TArray<uint8> data) {
		uint8 len1 = (messageData.Len() & 0xff000000UL) >> 24;
		uint8 len2 = (messageData.Len() & 0x00ff0000UL) >> 16;
		uint8 len3 = (messageData.Len() & 0x0000ff00UL) >> 8;
		uint8 len4 = (messageData.Len() & 0x000000ffUL);
		/*data.Insert(len1, 0);
		data.Insert(len2, 1);
		data.Insert(len3, 2);
		data.Insert(len4, 4);*/
		TArray<uint8> len;
		len.Insert(len1, 0);
		len.Insert(len2, 1);
		len.Insert(len3, 2);
		len.Insert(len4, 3);
		data.Append(len);
		data.Append((uint8*)TCHAR_TO_UTF8(messageData.GetCharArray().GetData()), messageData.Len());
		return data;
	};
	
};

USTRUCT(BlueprintType, Category = "GamePlatformService_Message")
struct FPlatformClientMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "GamePlatformService_Message")
	uint8 messageHeader;
	UPROPERTY(BlueprintReadOnly, Category = "GamePlatformService_Message")
	TArray<FPlatformMessageBlock> messageBlocks;
	UPROPERTY(BlueprintReadOnly, Category = "GamePlatformService_Message")
	uint8 messageEnd = 0x00;
	void LoadMessageData(TArray<uint8> data) {
		messageHeader = data.GetData()[0];
		int idx = 1;
		while (data.GetData()[idx] != 0)
		{
			FPlatformMessageBlock block;
			idx += block.LoadMessageBlock(data, idx);
			messageBlocks.Add(block);
		}
		
		//if(data.GetData()[idx + block.messageData.Len() + 4] == 0)
	}
	TArray<uint8> GetMessageData() {
		TArray<uint8> data;
		data.Insert(messageHeader, 0);
		for (int x = 0; x < messageBlocks.Num(); x++) {
			data = messageBlocks[x].WriteMessageBlockData(data);
		}
		data.Add(messageEnd);
		return data;
	}
};


