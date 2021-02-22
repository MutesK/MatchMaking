#pragma once


namespace GameRoom
{
	class IRoomInfo;
	using RoomPtr = std::shared_ptr<IRoomInfo>;
}

namespace DediServer
{
	enum class DediServerState
	{
		STOP,
		ALLOCATED,
		PLAYING,
	};
	using DediServerID = std::string;

	class IDediAllocateToRoomPolicy
	{
	protected:
		IDediAllocateToRoomPolicy();

		virtual bool CanAllocated(const GameRoom::RoomPtr& Ptr) = 0;

		virtual void DoAllocate(const GameRoom::RoomPtr& Ptr) = 0;
	};
	using IDediAllocatePolicyPtr = std::shared_ptr<IDediAllocateToRoomPolicy>;

	class IDediServerInfo
	{
	protected:
		DediServerID    _Id;
		DediServerState _State;
		IDediAllocatePolicyPtr _PolicyPtr;

		IDediServerInfo(const IDediAllocatePolicyPtr& Ptr);

		virtual void OnAllocated() = 0;

		virtual void OnGameStarted() = 0;

		virtual void OnGameEnded() = 0;

		virtual void OnDisconnected() = 0;

	private:
		bool RequestDedi(const GameRoom::RoomPtr& RequestorRoomPtr);
	};
	using IDediServerInfoPtr = std::shared_ptr<IDediServerInfo>;


	class DediPoolManager
	{
		IDediAllocatePolicyPtr _AllocatedPtr;
	public:
		DediPoolManager(const IDediAllocatePolicyPtr& GameRoomDediAllocatePtr);

		// DediServer -> DediPoolManager
		void AssignNewDedi(const DediServerID Key, const IDediServerInfoPtr& Ptr);
		void RemoveDedi(const DediServerID Key);
		void ChangeDediState(const DediServerID Key, DediServerState State);

		// Room Content -> DediPoolManager
		void RequestAvailableDedi(IDediServerInfoPtr& OUT Ptr, const GameRoom::RoomPtr& RequesterRoomPtr);
	};

}