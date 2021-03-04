#pragma once

namespace GameRoom
{
	class IMatchgTicket
	{
	};
	using IMatchTicketPtr = std::shared_ptr<IMatchgTicket>;

	using RoomID = std::string;
	class IFactoryRoomIDPolicy
	{
		virtual RoomID IssueRoomID() = 0;
	};
	using IFactoryRoomIDPolicyPtr = std::shared_ptr<IFactoryRoomIDPolicy>;

	class IJoinRoomPolicy
	{
		virtual bool CanJoinable(const IMatchTicketPtr Ptr) = 0;

		virtual bool CanJoinable(const std::vector<IMatchTicketPtr> Ptr) = 0;
	};
	using IJoinRoomPolicyPtr = std::shared_ptr<IJoinRoomPolicy>;

	class IFindDediPolicy
	{
		virtual void IsFindDedi() = 0;
	};
	using IFindDediPolicyPtr = std::shared_ptr<IFindDediPolicy>;


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

	class AbstractRoomInfo
	{
	protected:
		RoomState _State;

		AbstractRoomInfo(const RoomInfoParameters& Parameters);

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

