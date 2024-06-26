// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocatioIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBTService_PlayerLocatioIfSeen::UBTService_PlayerLocatioIfSeen()
{
    NodeName = "Update Player Location If Seen";
}

void UBTService_PlayerLocatioIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn == nullptr)
    {
        return;
    }

    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return;
    }
    
    if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }   
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
