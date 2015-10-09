#include <iostream>
#include <memory>
#include <vector>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "Analysis/EventSelector/interface/MuonMaker.h"

class EventBuilder : public edm::EDFilter {
  public :
    EventBuilder (const edm::ParameterSet&) ;
    ~EventBuilder () ; 

  private:
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    MuonMaker makeMuons ;

    bool makeMuons_ ; 

}; 

EventBuilder::EventBuilder(const edm::ParameterSet& pset) :
  makeMuons(pset.getParameter<edm::ParameterSet> ("muonParams")),
  makeMuons_(pset.getParameter<bool>("makeMuons")) 
{
  produces<vlq::MuonCollection>("MuonCollection");
}

EventBuilder::~EventBuilder () {} 

bool EventBuilder::filter (edm::Event& evt, const edm::EventSetup& iSetup) {
  using namespace edm;

  bool evtsel(0) ; 

  if ( makeMuons_ ) {
    vlq::MuonCollection muons_ ; 
    makeMuons(evt, muons_) ; 
    if (muons_.size() > 0) {
      std::auto_ptr<vlq::MuonCollection> muonCollection(new vlq::MuonCollection(muons_)) ; 
      evt.put(muonCollection, "MuonCollection") ; 
      evtsel = 1 ; 
    }
  }

  if ( evtsel ) return true ;
  else return false ; 
}

DEFINE_FWK_MODULE(EventBuilder);
