// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Engine.h"
#include "Misc/CommandLine.h"
#include "OutputDevice.h"
#include "Kismet/GameplayStatics.h"
#if PLATFORM_WINDOWS
#include "windows/WindowsWindow.h"
#include "SharedPointer.h"
#endif //PLATFORM_WINDOWS
#include "TimerManager.h"
#include "AllowWindowsPlatformTypes.h"
#include "HideWindowsPlatformTypes.h"

//#include "Runtime/ApplicationCore/Public/GenericPlatform/GenericApplication.h"
// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this,&AMyActor::BB);
	
	FString cmd = FString::Printf(TEXT("BB CD"));
	FOutputDeviceDebug device;
	CallFunctionByNameWithArguments(*cmd, device, NULL, true);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}
void AMyActor::AA()
{
	// Move window to the corresponding monitor
	if (GEngine && GEngine->GameViewport) {

		int MonitorNumber = 1;
		FParse::Value(FCommandLine::Get(), L"monitor=", MonitorNumber);

		FDisplayMetrics Display;
		FDisplayMetrics::GetDisplayMetrics(Display);

		int8 MonitorIndex = MonitorNumber - 1;
		int32 CurrentMonitorWidth = Display.MonitorInfo[MonitorIndex].NativeWidth;

		float WidthPosition = (MonitorIndex)*Display.PrimaryDisplayWidth - CurrentMonitorWidth;

		float HeightPosition = 0.0f;

		FVector2D WindowPosition = FVector2D((-1)*WidthPosition, HeightPosition);
		GEngine->GameViewport->GetWindow()->MoveWindowTo(WindowPosition);
	}
}
void AMyActor::AdjustWindow() {

#if PLATFORM_WINDOWS
	TSharedPtr<FGenericWindow> NativeWindow = GEngine->GameViewport->GetWindow()->GetNativeWindow();
	auto Window = static_cast<FWindowsWindow*>(NativeWindow.Get());
	//https://msdn.microsoft.com/en-us/library/windows/desktop/ms644898%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
	//https://msdn.microsoft.com/en-us/library/windows/desktop/ff700543(v=vs.85).aspx
	//DWORD WindowStyle = WS_DLGFRAME;
	DWORD WindowExStyle = WS_EX_APPWINDOW;
	DWORD WindowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX
		| WS_VISIBLE;
	//| WS_THICKFRAME | WS_POPUP | WS_DLGFRAME | WS_VISIBLE;

	auto hWnd = Window->GetHWnd();
	SetWindowLongPtr(hWnd, GWL_EXSTYLE, (LONG_PTR)WindowExStyle);
	SetWindowLongPtr(hWnd, GWL_STYLE, (LONG_PTR)WindowStyle);
#endif // #if PLATFORM_WINDOWS
}

void AMyActor::AAA_Implementation(int32 OtherBodyIndex, bool bFromSweep)
{
	UE_LOG(LogTemp, Warning, TEXT("Implenetaion in C++"));
}

void AMyActor::BB( AActor* OverlappedActor, AActor* OtherActor)
{
	
}
