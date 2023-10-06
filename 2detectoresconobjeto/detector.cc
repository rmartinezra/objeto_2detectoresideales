#include "detector.hh"
#include "G4SystemOfUnits.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : 
G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    //G4Track *track = aStep->GetTrack();

    //track->SetTrackStatus(fStopAndKill);// no propagar fotones despues de detectados

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    //G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    // G4ThreeVector momPhoton = preStepPoint->GetMomentum();
    G4double KE = preStepPoint->GetKineticEnergy();
    G4String particleName = aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();

    // * 3 formas de obtener la posicion de los fotones

    // * 1 imprime posiciones especificas de los fotones 

    //  * 2 trackin del foton en funcion de el detector golpeado
    
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    
    //G4int copuNo = touchable->GetCopyNumber();

    //G4count << "Copy number" << copyNo << G4endl;

    // * 3 dando la posicion del detector golpeado

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4cout << particleName <<" " << posDetector[0]<<" "<<posDetector[1]<<" "<< posDetector[2] <<" "<< KE <<G4endl;
    // analisis de datos root
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, 0, evt);
    man->FillNtupleDColumn(0, 1, posPhoton[0]);
    man->FillNtupleDColumn(0, 2, posPhoton[1]);
    man->FillNtupleDColumn(0, 3, posPhoton[2]);
    man->AddNtupleRow(0);
 }
