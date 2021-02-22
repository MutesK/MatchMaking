#pragma once

namespace GameRoom
{
	class IPlayerInfo
	{
	};
	using IPlayerInfoPtr = std::shared_ptr<IPlayerInfo>;

	using RoomID = std::string;
	class IFactoryRoomIDPolicy
	{
		virtual RoomID IssueRoomID() = 0;
	};
	using IFactoryRoomIDPolicyPtr = std::shared_ptr<IFactoryRoomIDPolicy>;

	class IJoinRoomPolicy
	{
		virtual bool CanJoinable(const IPlayerInfoPtr Ptr) = 0;

		virtual bool CanJoinable(const std::vector<IPlayerInfoPtr> Ptr) = 0;
	};
	using IJoinRoomPolicyPtr = std::shared_ptr<IJoinRoomPolicy>;

	class IFindDediPolicy
	{
		virtual void IsFindDedi() = 0;
	};
	using IFindDediPolicyPtr = std::shared_ptr<IFindDediPolicy>;

	// 여러가지 게임모드가 있을수있음 그에 따라 입장방법이 다를수있다.
	enum class GameRoomType
	{
	};

	enum class RoomState
	{
	};

	struct RoomInfoParameters
	{
		GameRoomType  _Type;
		IJoinRoomPolicyPtr _JoinCheckPtr;
		IFactoryRoomIDPolicyPtr _CreateIDPolicyPtr;
		IFindDediPolicyPtr     _IsFindDediTimingPolicy;
	};

	class IRoomInfo
	{
	protected:
		RoomState _State;

		IRoomInfo(const RoomInfoParameters& Parameters);

		friend class RoomManager;
	public:
		virtual bool RequestJoinPlayer(const IPlayerInfoPtr& PlayerPtr) = 0;

		RoomID GetRoomID() const;

		virtual void OnMatchSuccess() = 0;

		virtual void OnMatchFailed() = 0;

	private:
		void Comsume();
	};
	using RoomPtr = std::shared_ptr<IRoomInfo>;

	class RoomManager
	{
		std::unordered_map<RoomID, RoomPtr> _Rooms;
	public:
		void CreateRoom(size_t CreateRoomCount, RoomInfoParameters Parameters);

		void Comsume();
	};
}

