import FWCore.ParameterSet.Config as cms
from Analysis.EventSelector.MuonMaker_cfi import * 

EventBuilder = cms.EDFilter("EventBuilder",
    muonParams = defaultMuonParameters.clone(),  
    makeMuons  = cms.bool(True), 
    )

